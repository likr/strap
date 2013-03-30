#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include "common/core/index.hpp"
#include "common/core/class_indexed_data.hpp"
#include "mckp/algorithm/lp_relaxation.hpp"
#include "mmkp/core/problem.hpp"
#include "mmkp/algorithm/ecbb.hpp"
#include "mmkp/algorithm/normalize.hpp"


typedef int PType;
typedef int WType;
typedef strap::mmkp::Problem<PType, WType> Problem;


int main(int argc, char* argv[])
{
  std::string filename(argv[1]);

  std::ifstream in(filename.c_str());
  std::unique_ptr<Problem> problem(Problem::read(in));
  strap::mmkp::algorithm::normalize(*problem);

  std::cout << *problem << std::endl;

  auto start = std::chrono::system_clock::now();
  const auto* res = strap::mmkp::algorithm::ecbb(*problem, problem->index());
  auto stop = std::chrono::system_clock::now();
  auto time = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

  PType obj = problem->p_offset();
  for (const auto& klass : problem->index()) {
    const int i = klass.i();
    const int j = res->get(i);
    obj += problem->p(i, j);
    std::cout << "x[" << i << "] = " << j << std::endl;
  }
  std::cout << "optimal value: " << obj << std::endl;
  std::cout << "calculation time: " << time.count() << std::endl;
}
