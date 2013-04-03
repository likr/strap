#ifndef STRAP_MMKP_ALGORITHM_SURROGATE_CONSTRAINTS_HPP_
#define STRAP_MMKP_ALGORITHM_SURROGATE_CONSTRAINTS_HPP_

namespace strap {

class Index;
template<typename T> class ConstraintIndexedData;

namespace mckp {

template<typename PType, typename WType> class Problem;

}

namespace mmkp {

template<typename PType, typename WType> class Problem;

namespace algorithm {

template<typename PType, typename WType>
mckp::Problem<PType, double>* surrogate_constraints(
    const Problem<PType, WType>& problem);


template<typename PType, typename WType>
mckp::Problem<PType, double>* surrogate_constraints(
    const Problem<PType, WType>& problem,
    const Index& index);


template<typename PType, typename WType>
mckp::Problem<PType, double>* surrogate_constraints(
    const Problem<PType, WType>& problem,
    const ConstraintIndexedData<double>& u);


template<typename PType, typename WType>
mckp::Problem<PType, double>* surrogate_constraints(
    const Problem<PType, WType>& problem,
    const Index& index,
    const ConstraintIndexedData<double>& u);

} // namespace algorithm
} // namespace mmkp
} // namespace strap

#endif
