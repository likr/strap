#include <memory>
#include <strap/common/core/index.hpp>
#include <strap/common/core/indexed_data.hpp>
#include <strap/common/core/class_indexed_data.hpp>
#include <strap/mckp/core/problem.hpp>
#include "lp_relaxation.hpp"
#include "upper_bound.hpp"

namespace strap {
namespace mckp {
namespace algorithm {

template<typename PType, typename WType>
IndexedData<PType>* greedy_upper_bounds(const Problem<PType, WType>& problem)
{
  auto index = problem.index();
  return greedy_upper_bounds(problem, index);
}


template<typename PType, typename WType>
IndexedData<PType>* greedy_upper_bounds(
    const Problem<PType, WType>& problem,
    const Index& index)
{
  auto* upper_bounds = problem.data(PType(0));
  std::unique_ptr<LpRelaxationProblem<PType, WType> > lmck_problem(
      new LpRelaxationProblem<PType, WType>(problem, index));

  for (const auto& klass : index) {
    const int i = klass.i();
    auto sub_lmck_problem(*lmck_problem);

    sub_lmck_problem.remove(i);
    for (const int j : klass) {
      double sub_c = problem.c() - problem.w(i, j);
      upper_bounds->get(i, j) = problem.p(i, j) + sub_lmck_problem.solve(sub_c);
    }
  }

  return upper_bounds;
}


template<typename PType, typename WType>
IndexedData<PType>* dkw_upper_bounds(const Problem<PType, WType>& problem)
{
  auto index = problem.index();
  return dkw_upper_bounds(problem, index);
}


template<typename PType, typename WType>
IndexedData<PType>* dkw_upper_bounds(
    const Problem<PType, WType>& problem,
    const Index& index)
{
  auto* upper_bounds = problem.data(PType(0));
  std::unique_ptr<LpRelaxationProblem<PType, WType> > lmck_problem(
      new LpRelaxationProblem<PType, WType>(problem, index));
  std::unique_ptr<ClassIndexedData<int> > solution(
      lmck_problem->solve_with_solution());
  const double alpha = lmck_problem->alpha();
  PType ub = 0;
  WType remained_c = problem.c();

  for (const auto& klass : index) {
    ub += problem.p(klass.i(), solution->get(klass.i()));
    remained_c -= problem.w(klass.i(), solution->get(klass.i()));
  }
  for (const auto& klass : index) {
    const int i = klass.i();
    const int j0 = solution->get(i);
    for (const int j : klass) {
      const PType delta_p = problem.p(i, j) - problem.p(i, j0);
      const WType delta_w = problem.w(i, j) - problem.w(i, j0);
      upper_bounds->get(i, j) = ub + delta_p + alpha * (remained_c - delta_w);
    }
  }

  return upper_bounds;
}


template IndexedData<int>* greedy_upper_bounds(const Problem<int, int>& problem);
template IndexedData<int>* greedy_upper_bounds(const Problem<int, double>& problem);
template IndexedData<double>* greedy_upper_bounds(const Problem<double, int>& problem);
template IndexedData<double>* greedy_upper_bounds(const Problem<double, double>& problem);
template IndexedData<int>* dkw_upper_bounds(const Problem<int, int>& problem);
template IndexedData<int>* dkw_upper_bounds(const Problem<int, double>& problem);
template IndexedData<double>* dkw_upper_bounds(const Problem<double, int>& problem);
template IndexedData<double>* dkw_upper_bounds(const Problem<double, double>& problem);

} // namespace algorithm
} // namespace mckp
} // namespace strap
