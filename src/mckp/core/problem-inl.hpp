#ifndef STRAP_MCKP_CORE_PROBLEM_INL_HPP_
#define STRAP_MCKP_CORE_PROBLEM_INL_HPP_

#include "common/core/indexed_data.hpp"
#include "problem.hpp"

namespace strap {
namespace mckp {

template<typename PType, typename WType>
template<typename KInputIterator>
Problem<PType, WType>::Problem(
    const KInputIterator k_first, const KInputIterator k_last)
  : k_(k_first, k_last), offset_(k_.size()), m_(k_.size())
{
  for (int i = 1; i < m(); ++i) {
    offset_[i] = k_[i - 1] + offset_[i - 1];
  }
  n_ = k_.back() + offset_.back();
  p_.resize(n_);
  w_.resize(n_);
}


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
const WType& Problem<PType, WType>::w(const int i, const int j) const
{
  return w_[offset_[i] + j];
}


template<typename PType, typename WType>
WType& Problem<PType, WType>::w(const int i, const int j)
{
  return w_[offset_[i] + j];
}


template<typename PType, typename WType>
const WType& Problem<PType, WType>::c() const
{
  return c_;
}


template<typename PType, typename WType>
WType& Problem<PType, WType>::c()
{
  return c_;
}


template<typename PType, typename WType>
template<typename T>
IndexedData<T>* Problem<PType, WType>::data(const T init) const
{
  return new IndexedData<T>(k_.begin(), k_.end(), init);
}

} // namespace mckp
} // namespace strap

#endif
