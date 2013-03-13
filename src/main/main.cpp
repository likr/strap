#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include "mckp/algorithm/lp_relaxation.hpp"
#include "mmkp/core/problem.hpp"
#include "mmkp/algorithm/enumerate.hpp"
#include "mmkp/algorithm/entropy.hpp"
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
  double alpha = lmck_problem->alpha();
  std::cout << alpha << std::endl;

  auto* upper_bounds = problem->data<PType>();
  for (const auto& klass : problem->index()) {
    const int i = klass.i();
    auto sub_lmck_problem(*lmck_problem);

    sub_lmck_problem.remove(i);
    for (const int j : klass) {
      double sub_c = mck_problem->c() - mck_problem->w(i, j);
      upper_bounds->get(i, j) = mck_problem->p(i, j) + sub_lmck_problem.solve(sub_c);
    }
  }

  auto* entropy = strap::mmkp::algorithm::entropy<int>(
      *upper_bounds, upper_bound, 0, problem->index());
  for (const auto& klass : problem->index()) {
    const int i = klass.i();
    for (const int j : klass) {
      std::cout << i << ", " << j << ", " << upper_bounds->get(i, j) << std::endl;
    }
    std::cout << entropy->get(i) << std::endl << std::endl;
  }

  auto start = std::chrono::system_clock::now();
  auto res = strap::mmkp::algorithm::enumerate(*problem);
  auto stop = std::chrono::system_clock::now();
  auto time = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  std::cout << res << ' ' << time.count() << std::endl;
}
