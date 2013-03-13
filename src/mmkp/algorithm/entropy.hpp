#ifndef STRAP_MMKP_ALGORITHM_ENTROPY_HPP_
#define STRAP_MMKP_ALGORITHM_ENTROPY_HPP_

namespace strap {

class Index;
template<typename T> class IndexedData;
template<typename T> class ClassIndexedData;

namespace mmkp {

namespace algorithm {

template<typename PType>
double difficulty_entropy(
    const IndexedData<PType>& upper_bounds,
    const PType upper_bound,
    const PType lower_bound,
    const Index& index);


template<typename PType>
ClassIndexedData<double>* entropy(
    const IndexedData<PType>& upper_bounds,
    const PType upper_bound,
    const PType lower_bound,
    const Index& index);

} // namespace algorithm
} // namespace mmkp
} // namespace strap

#endif /* end of include guard */
