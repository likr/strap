#include <algorithm>
#include <numeric>
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
  : c_(problem.c())
{
  std::vector<LmckpItem<PType, WType> > lmckp_items;
  lmckp_items.reserve(problem.n() - problem.m());

  base_p_.reserve(index.size());
  base_w_.reserve(index.size());
  base_i_.reserve(index.size());
  base_j_.reserve(index.size());

  for (auto klass : index) {
    const int i = klass.i();

    dominate(problem, klass);
    lp_dominate(problem, klass);

    const int j = *klass.begin();

    PType p0 = problem.p(i, j);
    WType w0 = problem.w(i, j);
    base_p_.push_back(p0);
    base_w_.push_back(w0);
    base_i_.push_back(i);
    base_j_.push_back(j);

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

  p_[0] = std::accumulate(base_p_.begin(), base_p_.end(), PType(0));
  w_[0] = std::accumulate(base_w_.begin(), base_w_.end(), WType(0));
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
PType LpRelaxationProblem<PType, WType>::solve() const
{
  return solve(c_);
}


template<typename PType, typename WType>
PType LpRelaxationProblem<PType, WType>::solve(const WType c) const
{
  const int l = std::distance(
      w_.begin(),
      std::upper_bound(w_.begin(), w_.end(), c)) - 1;
  if (l == p_.size() - 1) {
    return p_.back();
  } else {
    return p_[l] + (c - w_[l]) * (p_[l + 1] - p_[l]) / (w_[l + 1] - w_[l]);
  }
}


template<typename PType, typename WType>
double LpRelaxationProblem<PType, WType>::alpha() const
{
  return alpha(c_);
}


template<typename PType, typename WType>
double LpRelaxationProblem<PType, WType>::alpha(const WType c) const
{
  auto it = std::upper_bound(w_.begin(), w_.end(), c);
  if (it == w_.end()) {
    return 0;
  } else {
    const int l = std::distance(
        w_.begin(),
        std::upper_bound(w_.begin(), w_.end(), c)) - 1;
    return double(p_[l + 1] - p_[l]) / (w_[l + 1] - w_[l]);
  }
}


template<typename PType, typename WType>
void LpRelaxationProblem<PType, WType>::remove(const int i)
{
  PType reduced_p(0);
  WType reduced_w(0);

  int base_index = std::distance(
      base_i_.begin(),
      std::find(base_i_.begin(), base_i_.end(), i));
  reduced_p += base_p_[base_index];
  reduced_w += base_w_[base_index];

  p_[0] -= reduced_p;
  w_[0] -= reduced_w;

  for (int l = 1; l < p_.size(); ++l) {
    if (i_[l] == i) {
      reduced_p = p_[l] - p_[l - 1];
      reduced_w = w_[l] - w_[l - 1];
    }
    p_[l] -= reduced_p;
    w_[l] -= reduced_w;
  }

  int index;
  index = 0;
  p_.resize(
      std::distance(
        p_.begin(),
        std::remove_if(
          p_.begin(),
          p_.end(),
          [&](const int p) {
            return i_[index++] == i;
          })));
  index = 0;
  w_.resize(
      std::distance(
        w_.begin(),
        std::remove_if(
          w_.begin(),
          w_.end(),
          [&](const int w) {
            return i_[index++] == i;
          })));
  index = 0;
  j_.resize(
      std::distance(
        j_.begin(),
        std::remove_if(
          j_.begin(),
          j_.end(),
          [&](const int j) {
            return i_[index++] == i;
          })));
  i_.resize(
      std::distance(
        i_.begin(),
        std::remove_if(
          i_.begin(),
          i_.end(),
          [i](const int i2) {
            return i == i2;
          })));
}


template class LpRelaxationProblem<int, int>;
template class LpRelaxationProblem<int, double>;
template class LpRelaxationProblem<double, int>;
template class LpRelaxationProblem<double, double>;

} // namespace algorithm
} // namespace mckp
} // namespace strap
