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
      solution_(problem.class_data(0)), current_solution_(problem.class_data(0)),
      sub_lmck_problems_(problem.m())
  {
    mck_problem_ = surrogate_constraints(problem_, index_);
    upper_bounds_ = mckp::algorithm::greedy_upper_bounds(*mck_problem_, index_);
    lmck_problem_ =
        new mckp::algorithm::LpRelaxationProblem<PType, double>(*mck_problem_, index_);
    base_solution_ = lmck_problem_->solve_with_solution();

    PType upper_bound(0);
    for (const auto& klass : index_) {
      const int i = klass.i();
      for (const int j : klass) {
        upper_bound = std::max(upper_bound, upper_bounds_->get(i, j));
      }
    }

    make_entropy_core(*upper_bounds_, upper_bound, PType(0), index_);
    sub_lmck_problems_[0] = new mckp::algorithm::LpRelaxationProblem<PType, double>(*lmck_problem_);
    sub_lmck_problems_[0]->remove(index_.at(0).i());
    for (int depth = 1; depth < problem_.m(); ++depth) {
      sub_lmck_problems_[depth] = new mckp::algorithm::LpRelaxationProblem<PType, double>(*sub_lmck_problems_[depth - 1]);
      sub_lmck_problems_[depth]->remove(index_.at(depth).i());
    }
  }


  ClassIndexedData<int>* operator()()
  {
    const int d = problem_.d();
    const int m = problem_.m();
    PType incumbent_value(0);
    auto* solution = new ClassIndexedData<int>(m);
    auto* incumbent_solution = new ClassIndexedData<int>(m);
    std::vector<PType> obj_stack(m);
    std::vector<WType> c_stack(m * d);
    std::vector<double> uc_stack(m);
    std::copy(
        problem_.c_begin(),
        problem_.c_end(),
        c_stack.begin());
    uc_stack[0] = mck_problem_->c();
    auto bottom_class = index_.at(m - 1);
    const int bottom_i = bottom_class.i();
    bottom_class.sort([&](const int j1, const int j2) {
          return problem_.p(bottom_class.i(), j1) >= problem_.p(bottom_class.i(), j2);
        });


    int leaf_count = 0;
    index_.traverse([&, d, m](const int depth, const int i, const int j) -> bool {
          solution->get(i) = j;
          const auto& item = problem_.item(i, j);
          if (upper_bounds_->get(i, j) < incumbent_value) {
            return false;
          }
          if (!this->is_feasible(c_stack.begin() + d * depth, item.w_begin(), d)) {
            return false;
          }
          const PType ub = sub_lmck_problems_[depth]->solve(uc_stack[depth] - mck_problem_->w(i, j));
          if (obj_stack[depth] + item.p() + ub < incumbent_value) {
            return false;
          }

          obj_stack[depth + 1] = obj_stack[depth] + item.p();
          uc_stack[depth + 1] = uc_stack[depth] - mck_problem_->w(i, j);
          for (const int k : constraint_index_) {
            c_stack[d * (depth + 1) + k] = c_stack[d * depth + k] - item.w(k);
          }

          if (depth == m - 2) {
            for (const int bottom_j : bottom_class) {
              const auto& bottom_item = problem_.item(bottom_i, bottom_j);
              if (obj_stack.back() + bottom_item.p() < incumbent_value) {
                break;
              }
              ++leaf_count;
              if (this->is_feasible(c_stack.begin() + d * (depth + 1), bottom_item.w_begin(), d)) {
                solution->get(bottom_i) = bottom_j;
                incumbent_value = obj_stack.back() + bottom_item.p();
                for (const auto& klass : this->index_) {
                  incumbent_solution->get(klass.i()) = solution->get(klass.i());
                }
                break;
              }
            }
            return false;
          } else {
            return true;
          }
        });
    std::cout << "number of leaf: " << leaf_count << std::endl;
    return incumbent_solution;
  }


private:
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


  const Problem<PType, WType>& problem_;
  Index index_;
  ConstraintIndex constraint_index_;

  ClassIndexedData<int>* solution_;
  ClassIndexedData<int>* current_solution_;

  IndexedData<PType>* upper_bounds_;
  mckp::Problem<PType, double>* mck_problem_;
  mckp::algorithm::LpRelaxationProblem<PType, double>* lmck_problem_;
  std::vector<mckp::algorithm::LpRelaxationProblem<PType, double>*> sub_lmck_problems_;
  ClassIndexedData<int>* base_solution_; // FIXME it must be delete
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
