#ifndef STRAP_MMKP_ALGORITHM_LMCK_BASE_SOLUTION_HPP_
#define STRAP_MMKP_ALGORITHM_LMCK_BASE_SOLUTION_HPP_

namespace strap {

template<typename T> class ClassIndexedData;

namespace mmkp {

template<typename PType, typename WType> class Problem;

namespace algorithm {

template<typename PType, typename WType>
ClassIndexedData<int>* lmck_base_solution(
    const Problem<PType, WType>& problem);

} // namespace algorithm
} // namespace mmkp
} // namespace strap

#endif /* end of include guard */
