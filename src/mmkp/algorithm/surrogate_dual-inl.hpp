#ifndef STRAP_MMKP_ALGORITHM_SURROGATE_DUAL_INL_HPP_
#define STRAP_MMKP_ALGORITHM_SURROGATE_DUAL_INL_HPP_

#include <memory>
#include "common/core/index.hpp"
#include "lp_relaxation.hpp"
#include "surrogate_dual.hpp"

namespace strap {
namespace mmkp {
namespace algorithm {

template<typename PType, typename WType, typename UOutputIterator>
PType surrogate_dual(
    const Problem<PType, WType>& problem,
    const Index& index,
    const UOutputIterator result)
{
  std::unique_ptr<LpRelaxationProblem> model(lp_relaxation(problem, index));
  model->setLogLevel(0);
  model->primal();

  auto out = result;
  for (int i = 0; i < problem.d(); ++i) {
    *out++ = model->dualRowSolution()[i];
  }

  return model->objectiveValue();
}

} // namespace algorithm
} // namespace mmkp
} // namespace strap

#endif
