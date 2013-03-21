#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>
#include "common/core/class.hpp"
#include "common/core/index.hpp"
#include "mckp/algorithm/lp_relaxation.hpp"
#include "mmkp/core/problem.hpp"
#include "mmkp/algorithm/entropy.hpp"
#include "mmkp/algorithm/surrogate_constraints.hpp"
#include "mmkp/algorithm/surrogate_dual.hpp"


typedef int PType;
typedef int WType;
typedef strap::mmkp::Problem<PType, WType> Problem;


strap::IndexedData<PType>* calculate_upper_bounds(
    const Problem& problem, const strap::Index& index,
    const strap::mckp::Problem<int, double>& mck_problem,
    const strap::mckp::algorithm::LpRelaxationProblem<int, double>& lmck_problem)
{
  auto* upper_bounds = problem.data(PType(0));

  for (const auto& klass : index) {
    const int i = klass.i();
    auto sub_lmck_problem(lmck_problem);

    sub_lmck_problem.remove(i);
    for (const int j : klass) {
      double sub_c = mck_problem.c() - mck_problem.w(i, j);
      upper_bounds->get(i, j) = mck_problem.p(i, j) + sub_lmck_problem.solve(sub_c);
    }
  }

  return upper_bounds;
}


void parameterized_entropy(const Problem& problem, const std::string& ofilename, double e)
{
  const auto index = problem.index();

  std::vector<double> u(problem.d());
  auto upper_bound =
    strap::mmkp::algorithm::surrogate_dual(problem, index, u.begin());

  std::unique_ptr<strap::mckp::Problem<int, double> > mck_problem(
      strap::mmkp::algorithm::surrogate_constraints(problem, index, u.begin()));
  std::unique_ptr<strap::mckp::algorithm::LpRelaxationProblem<int, double> > lmck_problem(
      new strap::mckp::algorithm::LpRelaxationProblem<int, double>(*mck_problem, index));

  const std::unique_ptr<strap::IndexedData<PType> > upper_bounds(calculate_upper_bounds(
        problem, index, *mck_problem, *lmck_problem));

  std::ofstream ofs(ofilename.c_str());
  for (int lower_bound = 0; lower_bound < upper_bound; ++lower_bound) {
    strap::Index index = problem.index();
    for (strap::Class& klass : index) {
      const int i = klass.i();
      klass.filter([&](const int j) {
            return upper_bounds->get(i, j) < lower_bound;
          });
    }
    std::unique_ptr<strap::ClassIndexedData<double> > entropy(
        strap::mmkp::algorithm::entropy(*upper_bounds, upper_bound, lower_bound, index, e));
    std::transform(
        index.begin(), index.end(),
        std::ostream_iterator<double>(ofs, ","),
        [&](const strap::Class& klass) -> double {
          return entropy->get(klass.i());
        });
    ofs << std::endl;
  }
}


int main(int argc, char* argv[])
{
  std::string ifilename(argv[1]);
  std::string ofilename(argv[2]);
  double e;
  if (argc == 4) {
    std::string estr(argv[3]);
    std::istringstream(estr) >> e;
  } else {
    e = strap::mmkp::algorithm::ENTROPY_E;
  }

  std::ifstream in(ifilename.c_str());
  std::unique_ptr<Problem> problem(Problem::read(in));

  parameterized_entropy(*problem, ofilename, e);
}
