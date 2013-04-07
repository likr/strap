#include <memory>
#include <strap/common/core/constraint_indexed_data.hpp>
#include <strap/common/core/index.hpp>
#include <strap/mmkp/core/problem.hpp>
#include "lp_relaxation.hpp"
#include "surrogate_dual.hpp"

namespace strap {
namespace mmkp {
namespace algorithm {

template<typename PType, typename WType>
ConstraintIndexedData<double>* surrogate_dual(
    const Problem<PType, WType>& problem)
{
  auto index = problem.index();
  return surrogate_dual(problem, index);
}


template<typename PType, typename WType>
ConstraintIndexedData<double>* surrogate_dual(
    const Problem<PType, WType>& problem, const Index& index)
{
  std::unique_ptr<LpRelaxationProblem> model(lp_relaxation(problem, index));
  model->setLogLevel(0);
  model->primal();

  auto* result = new ConstraintIndexedData<double>(problem.d());
  for (int k = 0; k < problem.d(); ++k) {
    result->get(k) = model->dualRowSolution()[k];
  }

  return result;
}


template ConstraintIndexedData<double>* surrogate_dual(
    const Problem<int, int>& problem);
template ConstraintIndexedData<double>* surrogate_dual(
    const Problem<int, double>& problem);
template ConstraintIndexedData<double>* surrogate_dual(
    const Problem<double, int>& problem);
template ConstraintIndexedData<double>* surrogate_dual(
    const Problem<double, double>& problem);

} // namespace algorithm
} // namespace mmkp
} // namespace strap
