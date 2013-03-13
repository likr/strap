#include <cmath>
#include <numeric>
#include <vector>
#include "common/core/index.hpp"
#include "common/core/indexed_data.hpp"
#include "common/core/class_indexed_data.hpp"
#include "mmkp/core/problem.hpp"
#include "entropy.hpp"

namespace strap {
namespace mmkp {
namespace algorithm {

template<class PType>
double theta_i(
    const PType upper_bound,
    const PType lower_bound,
    const PType fixed_upper_bound)
{
  const double E = -10.017;
  const double delta =
    double(upper_bound - fixed_upper_bound) / (upper_bound - lower_bound);
  const double phi = std::exp(E * delta) / 2;
  return phi / (1 - phi);
}


template<typename PType>
double class_entropy(
    const IndexedData<PType>& upper_bounds,
    const PType upper_bound,
    const PType lower_bound,
    const Class& klass)
{
  const int i = klass.i();
  const int k_i = klass.size();

  std::vector<double> theta(k_i);
  std::transform(
      klass.begin(), klass.end(),
      theta.begin(),
      [&](const int j) {
        return theta_i(upper_bound, lower_bound, upper_bounds.get(i, j));
      });

  double sum_theta = std::accumulate(theta.begin(), theta.end(), 0);
  return std::accumulate(
      theta.begin(), theta.end(), 0.0,
      [&](const double acc, const double theta_i) -> double {
        const double p_i = theta_i / sum_theta;
        const double h_i = p_i * std::log2(p_i);
        return acc - h_i;
      });
}


template<typename PType>
ClassIndexedData<double>* entropy(
    const IndexedData<PType>& upper_bounds,
    const PType upper_bound,
    const PType lower_bound,
    const Index& index)
{
  auto* result = new ClassIndexedData<double>(upper_bounds.m());

  for (const auto& klass : index) {
    const int i = klass.i();

    result->get(i) =
      class_entropy(upper_bounds, upper_bound, lower_bound, klass);
  }

  return result;
}


template<typename PType>
double difficulty_entropy(
    const IndexedData<PType>& upper_bounds,
    const PType upper_bound,
    const PType lower_bound,
    const Index& index)
{
  return std::accumulate(
      index.begin(), index.end(), 0.0,
      [&](const double acc, const Class& klass) -> double {
        return acc + class_entropy(
          upper_bounds, upper_bound, lower_bound, klass);
      });
}


template ClassIndexedData<double>* entropy(
    const IndexedData<int>& upper_bounds,
    const int upper_bound,
    const int lower_bound,
    const Index& index);
template ClassIndexedData<double>* entropy(
    const IndexedData<double>& upper_bounds,
    const double upper_bound,
    const double lower_bound,
    const Index& index);
template double difficulty_entropy(
    const IndexedData<int>& upper_bounds,
    const int upper_bound,
    const int lower_bound,
    const Index& index);
template double difficulty_entropy(
    const IndexedData<double>& upper_bounds,
    const double upper_bound,
    const double lower_bound,
    const Index& index);

} // namespace algorithm  
} // namespace mmkp
} // namespace strap