#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include "mckp/algorithm/lp_relaxation.hpp"
#include "mmkp/core/problem.hpp"
#include "mmkp/algorithm/enumerate.hpp"
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
  auto res = problem->p_offset() + strap::mmkp::algorithm::enumerate(*problem);
  auto stop = std::chrono::system_clock::now();
  auto time = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  std::cout << res << ' ' << time.count() << std::endl;
}
