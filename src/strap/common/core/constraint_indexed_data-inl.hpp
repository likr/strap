#ifndef STRAP_COMMON_CORE_CONSTRAINT_INDEXED_DATA_INL_HPP_
#define STRAP_COMMON_CORE_CONSTRAINT_INDEXED_DATA_INL_HPP_

#include "constraint_indexed_data.hpp"

namespace strap {

template<typename T>
ConstraintIndexedData<T>::ConstraintIndexedData()
{
}


template<typename T>
ConstraintIndexedData<T>::ConstraintIndexedData(const int d)
  : data_(d)
{
}


template<typename T>
ConstraintIndexedData<T>::ConstraintIndexedData(const int d, const T& init)
  : data_(d, init)
{
}


template<typename T>
int ConstraintIndexedData<T>::d() const
{
  return data_.size();
}


template<typename T>
T& ConstraintIndexedData<T>::get(const int k)
{
  return data_[k];
}


template<typename T>
const T& ConstraintIndexedData<T>::get(const int k) const
{
  return data_[k];
}
  
} // namespace strap

#endif /* end of include guard */
