#ifndef STRAP_MMKP_ALGORITHM_CONTINUOUS_SURROGATE_CONSTRAINS_RELAXATION_INL_HPP_
#define STRAP_MMKP_ALGORITHM_CONTINUOUS_SURROGATE_CONSTRAINS_RELAXATION_INL_HPP_

#include "continuous_surrogate_constraints_relaxation.hpp"
#include "surrogate_constraints.hpp"

namespace strap {
namespace mmkp {
namespace algorithm {

template<typename PType, typename WType>
template<typename UInputIterator>
ContinuousSurrogateConstraintsProblem<PType, WType>::ContinuousSurrogateConstraintsProblem(
    const Problem<PType, WType>& problem,
    const Index& index,
    const UInputIterator u_first)
{
}

} // namespace algorithm
} // namespace mmkp
} // namespace strap

#endif
