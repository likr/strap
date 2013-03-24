#ifndef STRAP_COMMON_CORE_INDEXED_DATA_INL_HPP_
#define STRAP_COMMON_CORE_INDEXED_DATA_INL_HPP_

#include "indexed_data.hpp"

namespace strap {

template<typename T>
template<typename KInputIterator>
IndexedData<T>::IndexedData(
    const KInputIterator k_first,
    const KInputIterator k_last)
  : offset_(k_first, k_last)
{
  for (int i = 0; i < offset_.size() - 1; ++i) {
    offset_[i + 1] += offset_[i];
  }
  data_.resize(offset_.back());
  for (int i = offset_.size() - 1; i >= 0; --i) {
    offset_[i] = offset_[i - 1];
  }
  offset_[0] = 0;
}


template<typename T>
template<typename KInputIterator>
IndexedData<T>::IndexedData(
    const KInputIterator k_first,
    const KInputIterator k_last,
    const T& init)
  : offset_(k_first, k_last)
{
  for (int i = 0, stop = offset_.size() - 1; i < stop; ++i) {
    offset_[i + 1] += offset_[i];
  }
  data_.resize(offset_.back());
  for (int i = offset_.size() - 1; i >= 0; --i) {
    offset_[i] = offset_[i - 1];
  }
  offset_[0] = 0;
}


template<typename T>
int IndexedData<T>::m() const
{
  return offset_.size();
}


template<typename T>
int IndexedData<T>::n() const
{
  return data_.size();
}


template<typename T>
T& IndexedData<T>::get(const int i, const int j)
{
  return data_[offset_[i] + j];
}


template<typename T>
const T& IndexedData<T>::get(const int i, const int j) const
{
  return data_[offset_[i] + j];
}

} // namespace strap

#endif /* end of include guard */
