#include <algorithm>
#include <vector>
#include <strap/common/core/index.hpp>
#include <strap/mmkp/core/problem.hpp>
#include "normalize.hpp"

namespace strap {
namespace mmkp {
namespace algorithm {

template<typename PType, typename WType>
Problem<PType, WType>* normalize_copy(const Problem<PType, WType>& problem)
{
  auto* normalized = new Problem<PType, WType>(problem);

  normalize(*normalized);

  return normalized;
}


template<typename PType, typename WType>
void normalize(Problem<PType, WType>& problem)
{
  const int d = problem.d();
  std::vector<WType> minimum_w(d);

  for (const auto& klass : problem.index()) {
    const int i = klass.i();
    const PType minimum_p = problem.p(
        i,
        *std::min_element(
          klass.begin(), klass.end(),
          [i, &problem](const int j1, const int j2) {
            return problem.p(i, j1) < problem.p(i, j2);
          }));
    for (int k = 0; k < d; ++k) {
      minimum_w[k] = problem.w(
          i,
          *std::min_element(
            klass.begin(), klass.end(),
            [i, k, &problem](const int j1, const int j2) {
              return problem.w(i, j1, k) < problem.w(i, j2, k);
            }),
          k);
    }
    for (const int j : klass) {
      problem.p(i, j) -= minimum_p;
      for (int k = 0; k < d; ++k) {
        problem.w(i, j, k) -= minimum_w[k];
      }
    }
    problem.p_offset() += minimum_p;
    for (int k = 0; k < d; ++k) {
      problem.c(k) -= minimum_w[k];
    }
  }
}


template Problem<int, int>* normalize_copy(const Problem<int, int>& problem);
template Problem<double, double>* normalize_copy(const Problem<double, double>& problem);


} // namespace algorithm
} // namespace mmkp
} // namespace strap
