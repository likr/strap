#ifndef STRAP_MMKP_ALGORITHM_SURROGATE_CONSTRAINTS_HPP_
#define STRAP_MMKP_ALGORITHM_SURROGATE_CONSTRAINTS_HPP_

namespace strap {

class Index;

namespace mckp {

template<typename PType, typename WType> class Problem;

}

namespace mmkp {

template<typename PType, typename WType> class Problem;

namespace algorithm {

template<typename PType, typename WType, typename UInputIterator>
mckp::Problem<PType, double>* surrogate_constraints(
    const Problem<PType, WType>& problem,
    const Index& index,
    const UInputIterator u_first);

} // namespace algorithm
} // namespace mmkp
} // namespace strap

#include "surrogate_constraints-inl.hpp"
#endif
