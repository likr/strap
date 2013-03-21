#ifndef STRAP_MMKP_ALGORITHM_ENUMERATE_HPP_
#define STRAP_MMKP_ALGORITHM_ENUMERATE_HPP_

namespace strap {

class Index;
template<typename T> class ClassIndexedData;

namespace mmkp {

template<typename PType, typename WType>
class Problem;

namespace algorithm {

template<typename PType, typename WType>
ClassIndexedData<int>* enumerate(const Problem<PType, WType>& problem);


template<typename PType, typename WType>
ClassIndexedData<int>* enumerate(const Problem<PType, WType>& problem, const Index& index);

} // namespace algorithm
} // namespace mmkp
} // namespace strap

#endif
