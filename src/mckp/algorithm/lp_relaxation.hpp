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
  PType solve() const;
  PType solve(const WType c) const;
  double alpha() const;
  double alpha(const WType c) const;
  void remove(const int i);


private:
  std::vector<PType> p_;
  std::vector<WType> w_;
  std::vector<int> i_;
  std::vector<int> j_;
  std::vector<PType> base_p_;
  std::vector<WType> base_w_;
  std::vector<int> base_i_;
  std::vector<int> base_j_;
  WType c_;
};

} // namespace algorithm
} // namespace mckp
} // namespace strap

#endif
