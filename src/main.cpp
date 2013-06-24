#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <picojson.h>
#include <strap/common/core/index.hpp>
#include <strap/common/core/class_indexed_data.hpp>
#include <strap/mckp/algorithm/lp_relaxation.hpp>
#include <strap/mmkp/core/problem.hpp>
#include <strap/mmkp/algorithm/ecbb.hpp>
#include <strap/mmkp/algorithm/normalize.hpp>


typedef int PType;
typedef int WType;
typedef strap::mmkp::Problem<PType, WType> Problem;


int main(int argc, char* argv[])
{
  std::string filename(argv[1]);

  std::ifstream in(filename.c_str());
  std::unique_ptr<Problem> problem(Problem::read(in));
  strap::mmkp::algorithm::normalize(*problem);

  std::cerr << "start calculation ..." << std::endl;

  auto start = std::chrono::system_clock::now();
  const auto* res = strap::mmkp::algorithm::ecbb(*problem, problem->index());
  auto stop = std::chrono::system_clock::now();
  auto time = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

  picojson::object result;
  picojson::array solution;

  PType obj = problem->p_offset();
  for (const auto& klass : problem->index()) {
    const int i = klass.i();
    const int j = res->get(i);
    obj += problem->p(i, j);
    solution.push_back(picojson::value((double)j));
  }

  result["solution"] = picojson::value(solution);
  result["calculation_time"] = picojson::value((double)time.count());
  result["optimal_value"] = picojson::value((double)obj);
  std::cout << picojson::value(result) << std::endl;
}
