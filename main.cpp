#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include "mmkp.hpp"
#include "enumerate.hpp"


typedef int PType;
typedef int WType;
typedef strap::Problem<PType, WType> Problem;

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
  for (int k = 0; k < problem.d(); ++k) {
    std::cout << problem.c(k) << ' ';
  }
  std::cout << std::endl;
  for (int i = 0; i < problem.m(); ++i) {
    std::cout << std::endl;
    for (int j = 0; j < problem.k(i); ++j) {
      std::cout << problem.p(i, j) << ' ';
      for (int k = 0; k < problem.d(); ++k) {
        std::cout << problem.w(i, j, k) << ' ';
      }
      std::cout << std::endl;
    }
  }
}


int main(int argc, char* argv[])
{
  std::string filename(argv[1]);

  Problem* problem = read(filename);

  dump(*problem);

  auto start = std::chrono::system_clock::now();
  auto res = strap::enumerate(*problem);
  auto stop = std::chrono::system_clock::now();
  auto time = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  std::cout << res << ' ' << time.count() << std::endl;
}
