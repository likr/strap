#ifndef STRAP_MMKP_ALGORITHM_ENTROPY_CORE_HPP_
#define STRAP_MMKP_ALGORITHM_ENTROPY_CORE_HPP_

namespace strap {

class Index;
template<typename T> class IndexedData;

namespace mmkp {
namespace algorithm {

extern const double ENTROPY_E;

template<typename PType>
void make_entropy_core(
    const IndexedData<PType>& upper_bounds,
    const PType upper_bound,
    const PType lower_bound,
    Index& index,
    const double e = ENTROPY_E);

} // namespace algorithm
} // namespace mmkp
} // namespace strap

#endif /* end of include guard */
