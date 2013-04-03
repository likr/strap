#include <strap/common/core/index.hpp>
#include "problem.hpp"

namespace strap {
namespace mckp {

template<typename PType, typename WType>
Problem<PType, WType>::Problem()
{
}


template<typename PType, typename WType>
Index Problem<PType, WType>::index() const
{
  return Index(k_.begin(), k_.end());
}

template class Problem<int, int>;
template class Problem<int, double>;
template class Problem<double, int>;
template class Problem<double, double>;

} // namespace mckp
} // namespace strap
