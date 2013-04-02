#ifndef STRAP_MMKP_ALGORITHM_ECBB_HPP_
#define STRAP_MMKP_ALGORITHM_ECBB_HPP_

namespace strap {

template<typename T> class ClassIndexedData;
class Index;

namespace mmkp {

template<typename PType, typename WType> class Problem;

namespace algorithm {

template<typename PType, typename WType>
ClassIndexedData<int>* ecbb(
    const Problem<PType, WType>& problem, const Index& index);

} // namespace algorithm
} // namespace mmkp
} // namespace strap

#endif /* end of include guard */
