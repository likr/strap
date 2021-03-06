#include <algorithm>
#include <memory>
#include <vector>
#include <strap/common/core/class_indexed_data.hpp>
#include <strap/common/core/constraint_index.hpp>
#include <strap/common/core/constraint_indexed_data.hpp>
#include <strap/common/core/index.hpp>
#include <strap/common/core/indexed_data.hpp>
#include <strap/mckp/core/problem.hpp>
#include <strap/mckp/algorithm/lp_relaxation.hpp>
#include <strap/mckp/algorithm/upper_bound.hpp>
#include <strap/mmkp/core/problem.hpp>
#include "entropy_core.hpp"
#include "surrogate_constraints.hpp"
#include "surrogate_dual.hpp"
#include "ecbb.hpp"

namespace strap {
namespace mmkp {
namespace algorithm {
namespace  {

template<typename PType, typename WType>
class Solver
{
public:
  Solver(const Problem<PType, WType>& problem, const Index& index)
    : problem_(problem), index_(index), constraint_index_(problem.constraint_index()),
      optimal_value_(0),
      solution_(problem.class_data(0)), current_solution_(problem.class_data(0)),
      upper_bound_(0), sub_lmck_problems_(problem.m()),
      d_(problem.d()), m_(problem.m())
  {
    mck_problem_ = surrogate_constraints(problem_, index_);
    upper_bounds_ = mckp::algorithm::greedy_upper_bounds(*mck_problem_, index_);
    lmck_problem_ =
        new mckp::algorithm::LpRelaxationProblem<PType, double>(*mck_problem_, index_);
    base_solution_ = lmck_problem_->solve_with_solution();

    for (const auto& klass : index_) {
      const int i = klass.i();
      for (const int j : klass) {
        upper_bound_ = std::max(upper_bound_, upper_bounds_->get(i, j));
      }
    }

    obj_stack_.resize(m_);
    c_stack_.resize(m_ * d_);
    uc_stack_.resize(m_);

    construct_core();
  }


  ClassIndexedData<int>* operator()()
  {
    while (search(0)) {
      construct_core();
    }
    return solution_;
  }


private:
  void construct_core()
  {
    std::copy(
        problem_.c_begin(),
        problem_.c_end(),
        c_stack_.begin());
    uc_stack_[0] = mck_problem_->c();

    make_entropy_core(*upper_bounds_, upper_bound_, optimal_value_, index_);
    std::reverse(index_.begin(), index_.end());

    sub_lmck_problems_[0] = new mckp::algorithm::LpRelaxationProblem<PType, double>(*lmck_problem_);
    sub_lmck_problems_[0]->remove(index_.at(0).i());
    for (int depth = 1; depth < m_; ++depth) {
      sub_lmck_problems_[depth] = new mckp::algorithm::LpRelaxationProblem<PType, double>(*sub_lmck_problems_[depth - 1]);
      sub_lmck_problems_[depth]->remove(index_.at(depth).i());
    }
  }


  template<typename CRandomAccessIterator, typename WRandomAccessIterator>
  bool is_feasible(
      CRandomAccessIterator c_first,
      WRandomAccessIterator w_first,
      int d)
  {
    for (int k = 0; k < d; ++k, ++c_first, ++w_first) {
      if (*w_first > *c_first) {
        return false;
      }
    }
    return true;
  }


  Class::const_iterator maximum_feasible_item(const Class& klass)
  {
    auto result = klass.end();
    PType obj(-1);
    const int i = klass.i();

    for (auto it = klass.begin(); it != klass.end(); ++it) {
      const int j = *it;
      const auto item = problem_.item(i, j);
      if (is_feasible(c_stack_.begin() + d_ * (m_ - 1), item.w_begin(), d_)) {
        if (item.p() > obj) {
          obj = item.p();
          result = it;
        }
      }
    }

    return result;
  }


  bool fathom(const int depth, const int i, const int j)
  {
    if (upper_bounds_->get(i, j) < optimal_value_) {
      return false;
    }

    const auto item = problem_.item(i, j);
    if (!is_feasible(c_stack_.begin() + d_ * depth, item.w_begin(), d_)) {
      return false;
    }

    const PType ub = sub_lmck_problems_[depth]->solve(uc_stack_[depth] - mck_problem_->w(i, j));
    if (obj_stack_[depth] + item.p() + ub < optimal_value_) {
      return false;
    }

    return true;
  }


  bool search(const int depth)
  {
    const Class& klass = index_.at(depth);
    const int i = klass.i();
    if (depth == m_ - 1) {
      const auto maximum_j = maximum_feasible_item(klass);
      if (maximum_j != klass.end()) {
        const PType obj = obj_stack_.back() + problem_.p(i, *maximum_j);
        if (obj > optimal_value_) {
          optimal_value_ = obj;
          std::cerr << "new solution found : " << optimal_value_ + problem_.p_offset() << std::endl;
          current_solution_->get(i) = *maximum_j;
          for (const auto& klass : index_) {
            solution_->get(klass.i()) = current_solution_->get(klass.i());
          }
          return true;
        }
      }
    } else {
      bool new_solution_found = false;
      for (const int j : klass) {
        const auto& item = problem_.item(i, j);
        if (fathom(depth, i, j)) {
          current_solution_->get(i) = j;
          obj_stack_[depth + 1] = obj_stack_[depth] + item.p();
          uc_stack_[depth + 1] = uc_stack_[depth] - mck_problem_->w(i, j);
          for (const int k : constraint_index_) {
            c_stack_[d_ * (depth + 1) + k]
              = c_stack_[d_ * depth + k] - item.w(k);
          }
          new_solution_found = new_solution_found || search(depth + 1);
        }
      }
      if (new_solution_found) {
        return true;
      }
    }
    return false;
  }


  const Problem<PType, WType>& problem_;
  Index index_;
  ConstraintIndex constraint_index_;

  PType optimal_value_;
  ClassIndexedData<int>* solution_;
  ClassIndexedData<int>* current_solution_;

  PType upper_bound_;
  IndexedData<PType>* upper_bounds_;
  mckp::Problem<PType, double>* mck_problem_;
  mckp::algorithm::LpRelaxationProblem<PType, double>* lmck_problem_;
  std::vector<mckp::algorithm::LpRelaxationProblem<PType, double>*> sub_lmck_problems_;
  ClassIndexedData<int>* base_solution_; // FIXME it must be delete

  std::vector<PType> obj_stack_;
  std::vector<WType> c_stack_;
  std::vector<double> uc_stack_;
  int d_;
  int m_;
};

} // namespace

template<typename PType, typename WType>
ClassIndexedData<int>* ecbb(const Problem<PType, WType>& problem)
{
  return ecbb(problem, problem.index());
}


template<typename PType, typename WType>
ClassIndexedData<int>* ecbb(
    const Problem<PType, WType>& problem,
    const Index& index)
{
  return Solver<PType, WType>(problem, index)();
}


template ClassIndexedData<int>* ecbb(
  const Problem<int, int>& problem);
template ClassIndexedData<int>* ecbb(
  const Problem<int, int>& problem, const Index& index);

} // namespace algorithm
} // namespace mmkp
} // namespace strap
