#ifndef STRAP_MCKP_ALGORITHM_LP_RELAXATION_HPP_
#define STRAP_MCKP_ALGORITHM_LP_RELAXATION_HPP_

#include <vector>

namespace strap {

class Index;

namespace mckp {

template<typename PType, typename WType> class Problem;

namespace algorithm {

template<typename PType, typename WType> 
class LpRelaxationProblem
{
public:
  LpRelaxationProblem(const Problem<PType, WType>& problem, const Index& index);
  PType solve(const WType c) const;


private:
  std::vector<PType> p_;
  std::vector<WType> w_;
  std::vector<int> i_;
  std::vector<int> j_;
};

} // namespace algorithm
} // namespace mckp
} // namespace strap

#endif
