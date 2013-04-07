#include <memory>
#include <strap/common/core/class.hpp>
#include <strap/common/core/class_indexed_data.hpp>
#include <strap/common/core/index.hpp>
#include <strap/common/core/indexed_data.hpp>
#include <strap/mckp/core/problem.hpp>
#include <strap/mckp/algorithm/upper_bound.hpp>
#include <strap/mmkp/core/problem.hpp>
#include <strap/mmkp/algorithm/surrogate_constraints.hpp>
#include "entropy.hpp"
#include "entropy_core.hpp"

namespace strap {
namespace mmkp {
namespace algorithm {

template<typename PType, typename WType>
Index* make_entropy_core(const Problem<PType, WType>& problem, const PType lower_bound)
{
  auto* result = new Index(problem.index());
  std::unique_ptr<mckp::Problem<PType, double> > mck_problem(
      surrogate_constraints(problem));
  std::unique_ptr<IndexedData<PType> > upper_bounds(mckp::algorithm::greedy_upper_bounds(*mck_problem));

  PType upper_bound(0);
  for (const auto& klass : *result) {
    const int i = klass.i();
    for (const int j : klass) {
      upper_bound = std::max(upper_bound, upper_bounds->get(i, j));
    }
  }

  make_entropy_core(*upper_bounds, upper_bound, lower_bound, *result);
  return result;
}


template<typename PType>
void make_entropy_core(
    const IndexedData<PType>& upper_bounds,
    const PType upper_bound,
    const PType lower_bound,
    Index& index,
    const double e)
{
  index.each([&](Class& klass) {
        const int i = klass.i();
        klass.remove_if([&](const int j) {
            return upper_bounds.get(i, j) < lower_bound;
          });
        klass.sort([&](const int j1, const int j2) {
            return upper_bounds.get(i, j1) > upper_bounds.get(i, j2);
          });
      });
  std::unique_ptr<ClassIndexedData<double> > h(
      entropy(upper_bounds, upper_bound, lower_bound, index));
  index.sort([&](const Class& klass1, const Class& klass2) {
        return h->get(klass1.i()) > h->get(klass2.i());
      });
}


template Index* make_entropy_core(const Problem<int, int>& problem, const int lower_bound);
template Index* make_entropy_core(const Problem<int, double>& problem, const int lower_bound);
template Index* make_entropy_core(const Problem<double, int>& problem, const double lower_bound);
template Index* make_entropy_core(const Problem<double, double>& problem, const double lower_bound);

} // namespace algorithm
} // namespace mmkp
} // namespace strap
