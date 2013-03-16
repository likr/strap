#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include "common/core/class.hpp"
#include "mckp/core/problem.hpp"
#include "lp_dominate.hpp"

namespace strap {
namespace mckp {
namespace algorithm {

template<typename PType, typename WType>
void lp_dominate(const Problem<PType, WType>& problem, Class& klass)
{
  if (klass.size() <= 2) {
    return;
  }

  std::vector<bool> stencil(klass.size(), false);
  const int i = klass.i();
  bool removed;

  do {
    removed = false;
    const auto first = stencil.begin();
    const auto last = stencil.end();

    for (auto it0 = first; it0 != last; ++it0) {
      const auto it1 = std::find(it0 + 1, last, false);
      if (it1 + 1 == last) {
        break;
      }
      const auto it2 = std::find(it1 + 1, last, false);
      if (it2 == last) {
        break;
      }

      const int j0 = klass[std::distance(first, it0)];
      const int j1 = klass[std::distance(first, it1)];
      const int j2 = klass[std::distance(first, it2)];

      const PType p0 = problem.p(i, j0);
      const WType w0 = problem.w(i, j0);
      const PType p1 = problem.p(i, j1);
      const WType w1 = problem.w(i, j1);
      const PType p2 = problem.p(i, j2);
      const WType w2 = problem.w(i, j2);
      const double slope1 = double(p1 - p0) / (w1 - w0);
      const double slope2 = double(p2 - p1) / (w2 - w1);

      if (slope1 <= slope2) {
        *it1 = true;
        removed = true;
      }
    }
  } while (removed);

  int l = 0;
  klass.filter(
      [&](const int j) {
        return stencil[l++];
      });
}


template void lp_dominate<int, int>(const Problem<int, int>&, Class&);
template void lp_dominate<int, double>(const Problem<int, double>&, Class&);
template void lp_dominate<double, int>(const Problem<double, int>&, Class&);
template void lp_dominate<double, double>(const Problem<double, double>&, Class&);

} // namespace algorithm
} // namespace mckp
} // namespace strap
