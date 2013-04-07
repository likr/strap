#ifndef STRAP_MMKP_ALGORITHM_SURROGATE_CONSTRAINTS_INL_HPP_
#define STRAP_MMKP_ALGORITHM_SURROGATE_CONSTRAINTS_INL_HPP_

#include <vector>
#include <strap/common/core/constraint_indexed_data.hpp>
#include <strap/common/core/index.hpp>
#include <strap/mckp/core/problem.hpp>
#include <strap/mmkp/core/problem.hpp>
#include "surrogate_constraints.hpp"
#include "surrogate_dual.hpp"

namespace strap {
namespace mmkp {
namespace algorithm {

template<typename PType, typename WType>
mckp::Problem<PType, double>* surrogate_constraints(
    const Problem<PType, WType>& problem)
{
  auto index = problem.index();
  return surrogate_constraints(problem, index);
}


template<typename PType, typename WType>
mckp::Problem<PType, double>* surrogate_constraints(
    const Problem<PType, WType>& problem,
    const Index& index)
{
  std::unique_ptr<ConstraintIndexedData<double> > u(surrogate_dual(problem, index));
  return surrogate_constraints(problem, index, *u);
}


template<typename PType, typename WType>
mckp::Problem<PType, double>* surrogate_constraints(
    const Problem<PType, WType>& problem,
    const ConstraintIndexedData<double>& u)
{
  auto index = problem.index();
  return surrogate_constraints(problem, index, u);
}


template<typename PType, typename WType>
mckp::Problem<PType, double>* surrogate_constraints(
    const Problem<PType, WType>& problem,
    const Index& index,
    const ConstraintIndexedData<double>& u)
{
  const int d = problem.d();

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
        uw += u.get(k) * item.w(k);
      }

      mck_problem->p(i, j) = item.p();
      mck_problem->w(i, j) = uw;
    }
  }

  double uc = 0;
  for (int k = 0; k < d; ++k) {
    uc += u.get(k) * problem.c(k);
  }
  mck_problem->c() = uc;

  return mck_problem;
}


template mckp::Problem<int, double>* surrogate_constraints(
    const Problem<int, int>& problem);
template mckp::Problem<int, double>* surrogate_constraints(
    const Problem<int, double>& problem);
template mckp::Problem<double, double>* surrogate_constraints(
    const Problem<double, int>& problem);
template mckp::Problem<double, double>* surrogate_constraints(
    const Problem<double, double>& problem);

} // namespace algorithm
} // namespace mmkp
} // namespace strap

#endif
