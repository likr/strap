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


template<typename PType, typename WType>
Index Problem<PType, WType>::index() const
{
  return Index(k_.begin(), k_.end());
}

template class Problem<int, int>;
template class Problem<double, double>;

} // namespace mmkp
} // namespace strap


template<typename PType, typename WType>
std::ostream& operator<<(std::ostream& out, const strap::mmkp::Problem<PType, WType>& problem)
{
  for (int k = 0; k < problem.d(); ++k) {
    out << problem.c(k) << ' ';
  }
  out << std::endl;
  out << std::endl;
  for (auto klass : problem.index()) {
    const int i = klass.i();
    for (auto j : klass) {
      out << problem.p(i, j) << ' ';
      for (int k = 0; k < problem.d(); ++k) {
        out << problem.w(i, j, k) << ' ';
      }
      out << std::endl;
    }
    out << std::endl;
  }
  return out;
}


template std::ostream& operator<<<int, int>(std::ostream& out, const strap::mmkp::Problem<int, int>& problem);
template std::ostream& operator<<<double, double>(std::ostream& out, const strap::mmkp::Problem<double, double>& problem);
