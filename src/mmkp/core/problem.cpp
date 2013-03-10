#include "problem.hpp"

namespace strap {
namespace mmkp {
  
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


template class Problem<int, int>;
template class Problem<double, double>;

} // namespace mmkp
} // namespace strap
