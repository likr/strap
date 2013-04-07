#ifndef STRAP_MMKP_ALGORITHM_BREAK_DIFFERENCE_CORE_HPP_
#define STRAP_MMKP_ALGORITHM_BREAK_DIFFERENCE_CORE_HPP_

namespace strap {

class Index;

namespace mmkp {

template<typename PType, typename WType> class Problem;

namespace algorithm {

template<typename PType, typename WType>
Index* make_break_difference_core(const Problem<PType, WType>& problem);

} // namespace algorithm
} // namespace mmkp
} // namespace strap

#endif /* end of include guard */
