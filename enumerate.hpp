#ifndef STRAP_ALGORITHM_ENUMERATE_HPP_
#define STRAP_ALGORITHM_ENUMERATE_HPP_

namespace strap {

template<typename PType, typename WType>
class Problem;

template<typename PType, typename WType>
PType enumerate(const Problem<PType, WType>& problem);

}
#endif
