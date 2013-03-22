#include "common/core/index.hpp"
#include "common/core/constraint_index.hpp"
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


template<typename PType, typename WType>
ConstraintIndex Problem<PType, WType>::constraint_index() const
{
  return ConstraintIndex(d_);
}


template<typename PType, typename WType>
Problem<PType, WType>* Problem<PType, WType>::read(std::istream& in)
{
  int m;
  in >> m;
  std::vector<int> k(m);
  for (int i = 0; i < m; ++i) {
    in >> k[i];
  }
  int d;
  in >> d;

  auto* problem = new Problem<PType, WType>(k, d);

  for (int k = 0; k < d; ++k) {
    in >> problem->c(k);
  }

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < problem->k(i); ++j) {
      in >> problem->p(i, j);
      for (int k = 0; k < d; ++k) {
        in >> problem->w(i, j, k);
      }
    }
  }

  return problem;
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
