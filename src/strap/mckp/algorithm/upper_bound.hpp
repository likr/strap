#ifndef STRAP_MCKP_ALGORITHM_UPPER_BOUND_HPP_
#define STRAP_MCKP_ALGORITHM_UPPER_BOUND_HPP_

namespace strap {

class Index;
template<typename T> class IndexedData;

namespace mckp {

template<typename PType, typename WType> class Problem;

namespace algorithm {

template<typename PType, typename WType>
IndexedData<PType>* greedy_upper_bounds(const Problem<PType, WType>& problem);


template<typename PType, typename WType>
IndexedData<PType>* greedy_upper_bounds(const Problem<PType, WType>& problem, const Index& index);


template<typename PType, typename WType>
IndexedData<PType>* dkw_upper_bounds(const Problem<PType, WType>& problem);


template<typename PType, typename WType>
IndexedData<PType>* dkw_upper_bounds(const Problem<PType, WType>& problem, const Index& index);

} // namespace algorithm
} // namespace mckp
} // namespace strap

#endif /* end of include guard */
