#ifndef STRAP_MMKP_ALGORITHM_SURROGATE_DUAL_HPP_
#define STRAP_MMKP_ALGORITHM_SURROGATE_DUAL_HPP_

namespace strap {

class Index;

namespace mmkp {

template<typename PType, typename WType> class Problem;

namespace algorithm {

template<typename PType, typename WType, typename UOutputIterator>
PType surrogate_dual(
    const Problem<PType, WType>& problem, const Index& index,
    const UOutputIterator result);

} // namespace alg
} // namespace mmkp
} // namespace strap

#include "surrogate_dual-inl.hpp"
#endif
