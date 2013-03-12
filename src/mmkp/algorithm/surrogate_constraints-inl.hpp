#ifndef STRAP_MMKP_ALGORITHM_SURROGATE_CONSTRAINTS_INL_HPP_
#define STRAP_MMKP_ALGORITHM_SURROGATE_CONSTRAINTS_INL_HPP_

#include <vector>
#include "common/core/index.hpp"
#include "mckp/core/problem.hpp"
#include "mmkp/core/problem.hpp"
#include "surrogate_constraints.hpp"

namespace strap {
namespace mmkp {
namespace algorithm {

template<typename PType, typename WType, typename UInputIterator>
mckp::Problem<PType, double>* surrogate_constraints(
    const Problem<PType, WType>& problem,
    const Index& index,
    const UInputIterator u_first)
{
  const int d = problem.d();

  std::vector<double> u;
  UInputIterator uiter = u_first;
  for (int k = 0; k < d; ++k) {
    u.push_back(*uiter++);
  }

  std::vector<int> k;
  for (const auto& klass : index) {
    k.push_back(klass.size());
  }

  auto* mck_problem = new mckp::Problem<PType, double>(k.begin(), k.end());

  for (const auto& klass : index) {
    const int i = klass.i();
    for (const int j : klass) {
      const auto& item = problem.item(i, j);
      double uw = 0;
      for (int k = 0; k < d; ++k) {
        uw += u[k] * item.w(k);
      }

      mck_problem->p(i, j) = item.p();
      mck_problem->w(i, j) = uw;
    }
  }

  double uc = 0;
  for (int k = 0; k < d; ++k) {
    uc += u[k] * problem.c(k);
  }
  mck_problem->c() = uc;

  return mck_problem;
}

} // namespace algorithm
} // namespace mmkp
} // namespace strap

#endif
