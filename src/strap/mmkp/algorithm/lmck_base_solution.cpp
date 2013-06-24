#include <memory>
#include <strap/common/core/class_indexed_data.hpp>
#include <strap/common/core/index.hpp>
#include <strap/mckp/core/problem.hpp>
#include <strap/mckp/algorithm/lp_relaxation.hpp>
#include <strap/mmkp/core/problem.hpp>
#include <strap/mmkp/algorithm/lmck_base_solution.hpp>
#include <strap/mmkp/algorithm/surrogate_constraints.hpp>

namespace strap {
namespace mmkp {
namespace algorithm {

template<typename PType, typename WType>
ClassIndexedData<int>* lmck_base_solution(
    const Problem<PType, WType>& problem)
{
  std::unique_ptr<mckp::Problem<PType, double> > mck_problem(surrogate_constraints(problem));
  std::unique_ptr<mckp::algorithm::LpRelaxationProblem<PType, double> >
    lmck_problem(new mckp::algorithm::LpRelaxationProblem<PType, double>(*mck_problem, problem.index()));
  return lmck_problem->solve_with_solution();
}

template ClassIndexedData<int>* lmck_base_solution(const Problem<int, int>& problem);
template ClassIndexedData<int>* lmck_base_solution(const Problem<int, double>& problem);
template ClassIndexedData<int>* lmck_base_solution(const Problem<double, int>& problem);
template ClassIndexedData<int>* lmck_base_solution(const Problem<double, double>& problem);

} // namespace algorithm
} // namespace mmkp
} // namespace strap
