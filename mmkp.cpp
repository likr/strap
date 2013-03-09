#include "mmkp.hpp"

namespace strap {

template<typename PType, typename WType>
Item<PType, WType>::Item(const PType* p, const WType* w, const int d)
  : p_(p), w_(w), d_(d)
{
}


template<typename PType, typename WType>
Item<PType, WType>::W::W(Item<PType, WType>& item)
  : item_(item)
{
}


template<typename PType, typename WType>
Problem<PType, WType>::Problem(const std::vector<int>& k, const int d)
  : k_(k), offset_(k.size()), c_(d), m_(k.size())
{
  for (int i = 1; i < m(); ++i) {
    offset_[i] = k_[i - 1] + offset_[i - 1];
  }
  n_ = k_.back() + offset_.back();
  d_ = d;
  p_.resize(n_);
  w_.resize(n_ * d);
}


template<typename PType, typename WType>
Item<PType, WType> Problem<PType, WType>::item(const int i, const int j) const
{
  return Item<PType, WType>(&p(i, j), &w(i, j, 0), d_);
}


template class Item<int, int>;
template class Item<double, double>;
template class Problem<int, int>;
template class Problem<double, double>;

}
