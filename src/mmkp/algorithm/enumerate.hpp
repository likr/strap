#ifndef STRAP_MMKP_ALGORITHM_ENUMERATE_HPP_
#define STRAP_MMKP_ALGORITHM_ENUMERATE_HPP_

namespace strap {
namespace mmkp {

template<typename PType, typename WType>
class Problem;

class Index;

namespace algorithm {

template<typename PType, typename WType>
PType enumerate(const Problem<PType, WType>& problem);


template<typename PType, typename WType>
PType enumerate(const Problem<PType, WType>& problem, const Index& index);

} // namespace algorithm
} // namespace mmkp
} // namespace strap

#endif
