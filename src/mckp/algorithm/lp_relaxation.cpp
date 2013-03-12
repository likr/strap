#include <algorithm>
#include <iostream>
#include <vector>
#include "common/core/index.hpp"
#include "mckp/core/problem.hpp"
#include "dominate.hpp"
#include "lp_dominate.hpp"
#include "lp_relaxation.hpp"

namespace strap {
namespace mckp {
namespace algorithm {
namespace {

template<typename PType, typename WType>
struct LmckpItem
{
  PType p;
  WType w;
  int i;
  int j;

  double efficiency() const
  {
    return double(p) / w;
  }
};

}

template<typename PType, typename WType>
LpRelaxationProblem<PType, WType>::LpRelaxationProblem(
    const Problem<PType, WType>& problem,
    const Index& index)
{
  std::vector<LmckpItem<PType, WType> > lmckp_items;
  lmckp_items.reserve(problem.n() - problem.m());

  PType base_p = 0;
  WType base_w = 0;

  for (auto klass : index) {
    const int i = klass.i();

    dominate(problem, klass);
    lp_dominate(problem, klass);

    const int j = *klass.begin();

    PType p0 = problem.p(i, j);
    WType w0 = problem.w(i, j);
    base_p += p0;
    base_w += w0;

    std::for_each(
        klass.begin() + 1, klass.end(),
        [&](const int j) {
          PType p = problem.p(i, j);
          WType w = problem.w(i, j);

          lmckp_items.push_back({p - p0, w - w0, i, j});
          p0 = p;
          w0 = w;
        });
  }
  std::sort(
      lmckp_items.begin(), lmckp_items.end(),
      [&](
          const LmckpItem<PType, WType>& item1,
          const LmckpItem<PType, WType>& item2) {
        return item1.efficiency() > item2.efficiency();
      });

  const int n = lmckp_items.size();

  p_.resize(n + 1);
  w_.resize(n + 1);
  i_.resize(n + 1);
  j_.resize(n + 1);

  p_[0] = base_p;
  w_[0] = base_w;
  i_[0] = -1;
  j_[0] = -1;

  for (int l = 1; l <= n; ++l) {
    const auto& item = lmckp_items[l - 1];
    p_[l] = p_[l - 1] + item.p;
    w_[l] = w_[l - 1] + item.w;
    i_[l] = item.i;
    j_[l] = item.j;
  }
}


template<typename PType, typename WType>
PType LpRelaxationProblem<PType, WType>::solve(const WType c) const
{
  const int l = std::distance(
      w_.begin(),
      std::upper_bound(w_.begin(), w_.end(), c)) - 1;
  return p_[l] + (c - w_[l]) * (p_[l + 1] - p_[l]) / (w_[l + 1] - w_[l]);
}


template class LpRelaxationProblem<int, int>;
template class LpRelaxationProblem<int, double>;
template class LpRelaxationProblem<double, int>;
template class LpRelaxationProblem<double, double>;

} // namespace algorithm
} // namespace mckp
} // namespace strap
