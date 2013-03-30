#include <algorithm>
#include "common/core/index.hpp"
#include "mckp/core/problem.hpp"
#include "dominate.hpp"

namespace strap {
namespace mckp {
namespace algorithm {

template<typename PType, typename WType>
void sort_by_dominate_order(const Problem<PType, WType>& problem, Class& klass)
{
  const int i = klass.i();
  std::sort(
      klass.begin(), klass.end(),
      [&](const int j1, const int j2) {
        if (problem.w(i, j1) == problem.w(i, j2)) {
          return problem.p(i, j1) > problem.p(i, j2);
        } else {
          return problem.w(i, j1) < problem.w(i, j2);
        }
      });
}


template<typename PType, typename WType>
void dominate(const Problem<PType, WType>& problem, Class& klass)
{
  const int i = klass.i();
  PType p0 = -1;

  sort_by_dominate_order(problem, klass);
  klass.remove_if([&](const int j) {
      const PType p = problem.p(i, j);
      if (p <= p0) {
        return true;
      } else {
        p0 = p;
        return false;
      }
  });
}

template void dominate<int, int>(const Problem<int, int>& problem, Class& klass);
template void dominate<int, double>(const Problem<int, double>& problem, Class& klass);
template void dominate<double, int>(const Problem<double, int>& problem, Class& klass);
template void dominate<double, double>(const Problem<double, double>& problem, Class& klass);

} // namespace algorithm
} // namespace mckp
} // namespace strap
