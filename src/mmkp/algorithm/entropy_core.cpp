#include <memory>
#include "common/core/class.hpp"
#include "common/core/class_indexed_data.hpp"
#include "common/core/index.hpp"
#include "common/core/indexed_data.hpp"
#include "entropy.hpp"
#include "entropy_core.hpp"

namespace strap {
namespace mmkp {
namespace algorithm {

template<typename PType>
void make_entropy_core(
    const IndexedData<PType>& upper_bounds,
    const PType upper_bound,
    const PType lower_bound,
    Index& index,
    const double e)
{
  index.each([&](Class& klass) {
        const int i = klass.i();
        klass.remove_if([&](const int j) {
            return upper_bounds.get(i, j) < lower_bound;
          });
        klass.sort([&](const int j1, const int j2) {
            return upper_bounds.get(i, j1) > upper_bounds.get(i, j2);
          });
      });
  std::unique_ptr<ClassIndexedData<double> > h(
      entropy(upper_bounds, upper_bound, lower_bound, index));
  index.sort([&](const Class& klass1, const Class& klass2) {
        return h->get(klass1.i()) > h->get(klass2.i());
      });
}


template void make_entropy_core<int>(
    const IndexedData<int>& upper_bounds,
    const int upper_bound,
    const int lower_bound,
    Index& index,
    const double e);

} // namespace algorithm
} // namespace mmkp
} // namespace strap
