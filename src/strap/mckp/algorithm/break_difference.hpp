#ifndef STRAP_MCKP_ALGORITHM_BREAK_DIFFERENCE_HPP_
#define STRAP_MCKP_ALGORITHM_BREAK_DIFFERENCE_HPP_

#include <cmath>
#include <memory>
#include <strap/common/core/class.hpp>
#include <strap/common/core/class_indexed_data.hpp>
#include <strap/mckp/core/problem.hpp>
#include "lp_dominate.hpp"
#include "lp_relaxation.hpp"

namespace strap {
namespace mckp {
namespace algorithm {

template<typename PType, typename WType>
ClassIndexedData<double>* break_differences(const Problem<PType, WType>& problem)
{
  std::unique_ptr<mckp::algorithm::LpRelaxationProblem<PType, double> > lmck_problem(
      new mckp::algorithm::LpRelaxationProblem<PType, double>(problem));
  const double alpha = lmck_problem->alpha();
  auto* break_differences = new ClassIndexedData<double>(problem.m());

  for (auto& klass : problem.index()) {
    const int i = klass.i();
    mckp::algorithm::lp_dominate(problem, klass);
    Class::iterator it0, it1;
    it0 = it1 = klass.begin();
    for (++it1; it1 != klass.end(); ++it0, ++it1) {
      const int j0 = *it0;
      const int j1 = *it1;
      const double alpha_i = double(problem.p(i, j1) - problem.p(i, j0)) /
        (problem.w(i, j1) - problem.w(i, j0));
      const double delta = std::abs(alpha - alpha_i);
      
      break_differences->get(i) = std::max(delta, alpha_i);
    }
  }

  return break_differences;
}

} // namespace algorithm
} // namespace mckp
} // namespace strap

#endif /* end of include guard */
