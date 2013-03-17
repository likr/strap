#ifndef STRAP_MMKP_ALGORITHM_NORMALIZE_HPP_
#define STRAP_MMKP_ALGORITHM_NORMALIZE_HPP_

namespace strap {

class Index;

namespace mmkp {

template<typename PType, typename WType> class Problem;

namespace algorithm {

template<typename PType, typename WType>
void normalize(Problem<PType, WType>& problem);


template<typename PType, typename WType>
Problem<PType, WType>* normalize_copy(const Problem<PType, WType>& problem);


template<typename PType, typename WType>
Problem<PType, WType>* normalize_copy(
    const Problem<PType, WType>& problem, const Index& index);

} // namespace algorithm
} // namespace mmkp
} // namespace strap
#endif /* end of include guard */
