#ifndef STRAP_MMKP_CORE_PROBLEM_INL_HPP_
#define STRAP_MMKP_CORE_PROBLEM_INL_HPP_

#include "common/core/indexed_data.hpp"
#include "common/core/class_indexed_data.hpp"
#include "problem.hpp"

namespace strap {
namespace mmkp {

template<typename PType, typename WType>
int Problem<PType, WType>::m() const
{
  return m_;
}


template<typename PType, typename WType>
int Problem<PType, WType>::n() const
{
  return n_;
}


template<typename PType, typename WType>
int Problem<PType, WType>::d() const
{
  return d_;
}


template<typename PType, typename WType>
int Problem<PType, WType>::k(const int i) const
{
  return k_[i];
}


template<typename PType, typename WType>
const PType& Problem<PType, WType>::p(const int i, const int j) const
{
  return p_[offset_[i] + j];
}


template<typename PType, typename WType>
PType& Problem<PType, WType>::p(const int i, const int j)
{
  return p_[offset_[i] + j];
}


template<typename PType, typename WType>
const WType& Problem<PType, WType>::w(const int i, const int j, const int k) const
{
  return w_[(offset_[i] + j) * d() + k];
}


template<typename PType, typename WType>
WType& Problem<PType, WType>::w(const int i, const int j, const int k)
{
  return w_[(offset_[i] + j) * d() + k];
}


template<typename PType, typename WType>
const WType& Problem<PType, WType>::c(const int k) const
{
  return c_[k];
}


template<typename PType, typename WType>
WType& Problem<PType, WType>::c(const int k)
{
  return c_[k];
}


template<typename PType, typename WType>
const typename Problem<PType, WType>::CRandomAccessIterator Problem<PType, WType>::c_begin() const
{
  return &c_[0];
}


template<typename PType, typename WType>
PType& Problem<PType, WType>::p_offset()
{
  return p_offset_;
}


template<typename PType, typename WType>
const PType& Problem<PType, WType>::p_offset() const
{
  return p_offset_;
}


template<typename PType, typename WType>
Item<PType, WType> Problem<PType, WType>::item(const int i, const int j) const
{
  return Item<PType, WType>(&p(i, j), &w(i, j, 0), d_);
}


template<typename PType, typename WType>
template<typename T>
IndexedData<T>* Problem<PType, WType>::data(const T init) const
{
  return new IndexedData<T>(k_.begin(), k_.end(), init);
}


template<typename PType, typename WType>
template<typename T>
ClassIndexedData<T>* Problem<PType, WType>::class_data(const T init) const
{
  return new ClassIndexedData<T>(m_, init);
}

} // namespace mmkp
} // namespace strap

#endif
