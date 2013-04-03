#ifndef STRAP_MMKP_ALGORITHM_SURROGATE_DUAL_HPP_
#define STRAP_MMKP_ALGORITHM_SURROGATE_DUAL_HPP_

namespace strap {

class Index;
template<typename T> class ConstraintIndexedData;

namespace mmkp {

template<typename PType, typename WType> class Problem;

namespace algorithm {

template<typename PType, typename WType>
ConstraintIndexedData<double>* surrogate_dual(
    const Problem<PType, WType>& problem);


template<typename PType, typename WType>
ConstraintIndexedData<double>* surrogate_dual(
    const Problem<PType, WType>& problem, const Index& index);

} // namespace alg
} // namespace mmkp
} // namespace strap

#endif
