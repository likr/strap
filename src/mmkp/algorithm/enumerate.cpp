#include <vector>
#include "common/core/index.hpp"
#include "common/core/constraint_index.hpp"
#include "common/core/class_indexed_data.hpp"
#include "mmkp/core/problem.hpp"
#include "enumerate.hpp"

namespace strap {
namespace mmkp {
namespace algorithm {
namespace {

template<typename PType, typename WType>
struct Solver
{
public:
  Solver(const Problem<PType, WType>& problem, const Index& index)
    : problem_(problem), index_(index),
      constraint_index_(problem.constraint_index()),
      bottom_(problem.m() - 1), d_(problem.d()),
      lower_bound_(0)
  {
    c_stack_ = new WType[problem.m() * problem.d()];
    for (const int k : constraint_index_) {
      c_stack_[k] = problem.c(k);
    }
    solution_ = problem.class_data(0);
    incumbent_solution_ = problem.class_data(0);
  }


  ~Solver()
  {
    delete[] c_stack_;
    delete solution_;
  }


  ClassIndexedData<int>* operator()()
  {
    search(0, 0);
    return incumbent_solution_;
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


  void search(const int a, const PType obj)
  {
    WType* c = c_stack_ + a * d_;
    const auto& klass = index_.at(a);
    const int i = klass.i();

    if (a == bottom_) {
      PType lower_bound(0);
      for (auto j : klass) {
        const Item<PType, WType> item = problem_.item(i, j);
        if (is_feasible(c, item.w_begin(), d_)) {
          if (item.p() > lower_bound) {
            lower_bound = item.p();
            solution_->get(i) = j;
          }
        }
      }
      lower_bound += obj;
      if (lower_bound > lower_bound_) {
        lower_bound_ = lower_bound;
        for (const auto& klass : index_) {
          incumbent_solution_->get(klass.i()) = solution_->get(klass.i());
        }
      }
    } else {
      WType* new_c = c + d_;
      for (auto j : klass) {
        const Item<PType, WType> item = problem_.item(i, j);
        bool is_feasible = true;
        for (const int k : constraint_index_) {
          new_c[k] = c[k] - item.w(k);
          if (new_c[k] < 0) {
            is_feasible = false;
            break;
          }
        }

        if (is_feasible) {
          solution_->get(i) = j;
          search(a + 1, obj + item.p());
        }
      }
    }
  }

  const Problem<PType, WType>& problem_;
  const Index index_;
  const ConstraintIndex constraint_index_;
  int bottom_;
  int d_;
  WType* c_stack_;
  PType lower_bound_;
  ClassIndexedData<int>* solution_;
  ClassIndexedData<int>* incumbent_solution_;
};

}

template<typename PType, typename WType>
ClassIndexedData<int>* enumerate(const Problem<PType, WType>& problem)
{
  return enumerate(problem, problem.index());
}


template<typename PType, typename WType>
ClassIndexedData<int>* enumerate(const Problem<PType, WType>& problem, const Index& index)
{
  return Solver<PType, WType>(problem, index)();
}

template ClassIndexedData<int>* enumerate<int, int>(const Problem<int, int>&);
template ClassIndexedData<int>* enumerate<double, double>(const Problem<double, double>&);

} // namespace algorithm
} // namespace mmkp
} // namespace strap
