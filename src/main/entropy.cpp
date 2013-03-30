#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>
#include "common/core/class.hpp"
#include "common/core/index.hpp"
#include "mckp/algorithm/lp_relaxation.hpp"
#include "mckp/algorithm/upper_bound.hpp"
#include "mmkp/core/problem.hpp"
#include "mmkp/algorithm/entropy.hpp"
#include "mmkp/algorithm/surrogate_constraints.hpp"
#include "mmkp/algorithm/surrogate_dual.hpp"


typedef int PType;
typedef int WType;
typedef strap::mmkp::Problem<PType, WType> Problem;


void parameterized_entropy(const Problem& problem, const std::string& ofilename, double e)
{
  const auto index = problem.index();

  std::vector<double> u(problem.d());
  auto upper_bound =
    strap::mmkp::algorithm::surrogate_dual(problem, index, u.begin());

  std::unique_ptr<strap::mckp::Problem<int, double> > mck_problem(
      strap::mmkp::algorithm::surrogate_constraints(problem, index, u.begin()));

  const std::unique_ptr<strap::IndexedData<PType> > upper_bounds(
      strap::mckp::algorithm::dkw_upper_bounds(*mck_problem, index));

  for (const auto& klass : index) {
    const int i = klass.i();
    std::cout << i << std::endl;
    for (const int j : klass) {
      std::cout << upper_bounds->get(i, j) << std::endl;;
    }
    std::cout << std::endl;
  }

  std::ofstream ofs(ofilename.c_str());
  for (int lower_bound = 0; lower_bound < upper_bound; ++lower_bound) {
    strap::Index index = problem.index();
    for (strap::Class& klass : index) {
      const int i = klass.i();
      klass.remove_if([&](const int j) {
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
