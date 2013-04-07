#include <algorithm>
#include <cmath>
#include <memory>
#include <strap/common/core/index.hpp>
#include <strap/mckp/core/problem.hpp>
#include <strap/mckp/algorithm/lp_dominate.hpp>
#include <strap/mckp/algorithm/lp_relaxation.hpp>
#include <strap/mmkp/core/problem.hpp>
#include "break_difference_core.hpp"
#include "surrogate_constraints.hpp"

namespace strap {
namespace mmkp {
namespace algorithm {

template<typename PType, typename WType>
Index* make_break_difference_core(const Problem<PType, WType>& problem)
{
  auto* result = new Index(problem.index());
  std::unique_ptr<mckp::Problem<PType, double> > mck_problem(
      surrogate_constraints(problem));
  std::unique_ptr<mckp::algorithm::LpRelaxationProblem<PType, double> > lmck_problem(
      new mckp::algorithm::LpRelaxationProblem<PType, double>(*mck_problem, *result));
  const double alpha = lmck_problem->alpha();
  std::unique_ptr<ClassIndexedData<double> > break_differences(
      new ClassIndexedData<double>(problem.m()));

  for (const auto& klass : *result) {
    const int i = klass.i();
    Class lp_dominated_class(klass);

    mckp::algorithm::lp_dominate(*mck_problem, lp_dominated_class);
    Class::iterator it0, it1;
    it0 = it1 = lp_dominated_class.begin();
    for (++it1; it1 != lp_dominated_class.end(); ++it0, ++it1) {
      const int j0 = *it0;
      const int j1 = *it1;
      const double alpha_i = double(mck_problem->p(i, j1) - mck_problem->p(i, j0)) /
        (mck_problem->w(i, j1) - mck_problem->w(i, j0));
      const double delta = std::abs(alpha - alpha_i);
      
      break_differences->get(i) = std::max(delta, alpha_i);
    }
  }

  std::sort(
      result->begin(), result->end(),
      [&break_differences](const Class& class1, const Class& class2) {
        return break_differences->get(class1.i()) < break_differences->get(class2.i());
      });
  return result;
}


template Index* make_break_difference_core(const Problem<int, int>& problem);
template Index* make_break_difference_core(const Problem<int, double>& problem);
template Index* make_break_difference_core(const Problem<double, int>& problem);
template Index* make_break_difference_core(const Problem<double, double>& problem);

} // namespace algorithm
} // namespace mmkp
} // namespace strap
