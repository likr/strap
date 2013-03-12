#include "common/core/index.hpp"
#include "mmkp/core/problem.hpp"
#include "lp_relaxation.hpp"

namespace strap {
namespace mmkp {
namespace algorithm {

template<typename PType, typename WType>
LpRelaxationProblem* lp_relaxation(
    const Problem<PType, WType>& problem,
    const Index& index)
{
  const int m = index.size();
  const int d = problem.d();

  ClpSimplex* model = new ClpSimplex();
  model->setOptimizationDirection(-1);
  model->resize(d + m, 0);

  for (int k = 0; k < d; ++k) {
    model->setRowBounds(k, 0, problem.c(k));
  }
  for (int i = 0; i < m; ++i) {
    model->setRowBounds(d + i, 1, 1);
  }

  std::vector<int> indices(d + 1);
  for (int k = 0; k < d; ++k) {
    indices[k] = k;
  }
  indices[d] = d;

  std::vector<double> elements(d + 1);
  elements[d] = 1;
  for (const auto& klass : index) {
    const int i = klass.i();
    for (int j : klass) {
      const auto& item = problem.item(i, j);
      std::copy(item.w().begin(), item.w().end(), elements.begin());
      model->addColumn(d + 1, &indices[0], &elements[0], 0, 1, item.p());
    }
    ++indices[d];
  }

  return model;
}

template LpRelaxationProblem* lp_relaxation<int, int>(
    const Problem<int, int>& problem, const Index& index);
template LpRelaxationProblem* lp_relaxation<double, double>(
    const Problem<double, double>& problem, const Index& index);

} // namespace algorithm
} // namespace mmkp
} // namespace strap
