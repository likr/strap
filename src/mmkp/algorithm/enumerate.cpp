#include <vector>
#include "common/core/index.hpp"
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
      bottom_(problem.m() - 1), d_(problem.d())
  {
    c_stack_ = new WType[problem.m() * problem.d()];
    for (int k = 0; k < d_; ++k) {
      c_stack_[k] = problem.c(k);
    }
  }


  ~Solver()
  {
    delete[] c_stack_;
  }


  PType operator()()
  {
    return search(0, 0);
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


  PType search(const int a, const PType obj)
  {
    PType lower_bound(0);
    WType* c = c_stack_ + a * d_;
    const auto& klass = index_.at(a);
    const int i = klass.i();

    if (a == bottom_) {
      for (auto j : klass) {
        const Item<PType, WType> item = problem_.item(i, j);
        if (is_feasible(c, item.w_begin(), d_)) {
          lower_bound = std::max(lower_bound, item.p());
        }
      }
      lower_bound += obj;
    } else {
      WType* new_c = c + d_;
      for (auto j : klass) {
        const Item<PType, WType> item = problem_.item(i, j);
        bool is_feasible = true;
        for (int k = 0; k < d_; ++k) {
          new_c[k] = c[k] - item.w(k);
          if (new_c[k] < 0) {
            is_feasible = false;
            break;
          }
        }

        if (is_feasible) {
          lower_bound = std::max(
              lower_bound,
              search(a + 1, obj + item.p()));
        }
      }
    }

    return lower_bound;
  }

  const Problem<PType, WType>& problem_;
  const Index& index_;
  int bottom_;
  int d_;
  WType* c_stack_;
};

}

template<typename PType, typename WType>
PType enumerate(const Problem<PType, WType>& problem)
{
  return enumerate(problem, problem.index());
}


template<typename PType, typename WType>
PType enumerate(const Problem<PType, WType>& problem, const Index& index)
{
  return Solver<PType, WType>(problem, index)();
}

template int enumerate<int, int>(const Problem<int, int>&);
template double enumerate<double, double>(const Problem<double, double>&);

} // namespace algorithm
} // namespace mmkp
} // namespace strap
