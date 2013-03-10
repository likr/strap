#ifndef STRAP_MMKP_CORE_ITEM_INL_HPP_
#define STRAP_MMKP_CORE_ITEM_INL_HPP_

#include "item.hpp"

namespace strap {
namespace mmkp {

template<typename PType, typename WType>
const PType& Item<PType, WType>::p() const
{
  return *p_;
}


template<typename PType, typename WType> 
const WType& Item<PType, WType>::w(const int k) const
{
  return *(w_ + k);
}


template<typename PType, typename WType>
const typename Item<PType, WType>::WRandomAccessIterator Item<PType, WType>::w_begin() const
{
  return w_;
}


template<typename PType, typename WType>
const typename Item<PType, WType>::WRandomAccessIterator Item<PType, WType>::w_end() const
{
  return w_ + d_;
}


template<typename PType, typename WType>
const typename Item<PType, WType>::WRandomAccessIterator Item<PType, WType>::W::begin() const
{
  return item_.w_;
}


template<typename PType, typename WType>
const typename Item<PType, WType>::WRandomAccessIterator Item<PType, WType>::W::end() const
{
  return item_.w_ + item_.d_;
}

} // namespace mmkp
} // namespace strap

#endif
