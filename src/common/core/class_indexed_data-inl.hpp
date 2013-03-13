#ifndef STRAP_COMMON_CORE_CLASS_INDEXED_DATA_INL_HPP_
#define STRAP_COMMON_CORE_CLASS_INDEXED_DATA_INL_HPP_

#include "class_indexed_data.hpp"

namespace strap {

template<typename T>
ClassIndexedData<T>::ClassIndexedData(const int m)
  : data_(m)
{
}


template<typename T>
int ClassIndexedData<T>::m() const
{
  return data_.size();
}


template<typename T>
T& ClassIndexedData<T>::get(const int i)
{
  return data_[i];
}


template<typename T>
const T& ClassIndexedData<T>::get(const int i) const
{
  return data_[i];
}

} // namespace strap
#endif /* end of include guard */
