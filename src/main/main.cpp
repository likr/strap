#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include "mckp/algorithm/lp_relaxation.hpp"
#include "mmkp/core/problem.hpp"
#include "mmkp/algorithm/enumerate.hpp"
#include "mmkp/algorithm/surrogate_constraints.hpp"
#include "mmkp/algorithm/surrogate_dual.hpp"


typedef int PType;
typedef int WType;
typedef strap::mmkp::Problem<PType, WType> Problem;

Problem* read(const std::string& filename)
{
  std::ifstream ifs(filename.c_str());

  int m;
  ifs >> m;
  std::vector<int> k(m);
  for (int i = 0; i < m; ++i) {
    ifs >> k[i];
  }
  int d;
  ifs >> d;

  Problem* problem = new Problem(k, d);

  for (int k = 0; k < d; ++k) {
    ifs >> problem->c(k);
  }

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < problem->k(i); ++j) {
      ifs >> problem->p(i, j);
      for (int k = 0; k < d; ++k) {
        ifs >> problem->w(i, j, k);
      }
    }
  }

  return problem;
}


void dump(const Problem& problem)
{
  std::cout << problem;
}


int main(int argc, char* argv[])
{
  std::string filename(argv[1]);

  std::unique_ptr<Problem> problem(read(filename));

  dump(*problem);

  std::vector<double> u(problem->d());
  auto upper_bound = strap::mmkp::algorithm::surrogate_dual(
      *problem, problem->index(), u.begin());
  std::cout << upper_bound << std::endl;
  std::copy(
      u.begin(), u.end(),
      std::ostream_iterator<double>(std::cout, " "));
  std::cout << std::endl;
  std::cout << std::endl;


  auto* mck_problem = strap::mmkp::algorithm::surrogate_constraints(
      *problem, problem->index(), u.begin());
  auto* lmck_problem =
    new strap::mckp::algorithm::LpRelaxationProblem<int, double>(
        *mck_problem, problem->index());
  std::cout << lmck_problem->solve(mck_problem->c()) << std::endl;;


  auto start = std::chrono::system_clock::now();
  auto res = strap::mmkp::algorithm::enumerate(*problem);
  auto stop = std::chrono::system_clock::now();
  auto time = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  std::cout << res << ' ' << time.count() << std::endl;
}
