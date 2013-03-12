#ifndef STRAP_MMKP_ALGORITHM_CONTINUOUS_SURROGATE_CONSTRAINS_RELAXATION_HPP_
#define STRAP_MMKP_ALGORITHM_CONTINUOUS_SURROGATE_CONSTRAINS_RELAXATION_HPP_

#include "mmkp/core/index.hpp"
#include "mmkp/core/problem.hpp"

namespace strap {
namespace mmkp {
namespace algorithm { 

template<typename PType, typename WType>
class ContinuousSurrogateConstraintsProblem
{
public:
  template<typename UInputIterator>
  ContinuousSurrogateConstraintsProblem(
      const Problem<PType, WType>& problem,
      const Index& index,
      const UInputIterator u_first);
};

} // namespace algorithm
} // namespace mmkp
} // namespace strap

#include "continuous_surrogate_constraints_relaxation-inl.hpp"
#endif
