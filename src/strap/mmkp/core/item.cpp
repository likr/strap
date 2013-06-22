#include "item.hpp"

namespace strap {
namespace mmkp {
  
template<typename PType, typename WType>
Item<PType, WType>::Item()
{
}


template<typename PType, typename WType>
Item<PType, WType>::Item(const PType* p, const WType* w, const int d)
  : p_(p), w_(w), d_(d)
{
}


template<typename PType, typename WType>
Item<PType, WType>::W::W(const Item<PType, WType>& item)
  : item_(item)
{
}


template class Item<int, int>;
template class Item<int, double>;
template class Item<double, int>;
template class Item<double, double>;

} // namespace mmkp
} // namespace strap
