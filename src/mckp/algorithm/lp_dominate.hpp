#ifndef STRAP_MCKP_ALGORITHM_LP_DOMINATE_HPP_
#define STRAP_MCKP_ALGORITHM_LP_DOMINATE_HPP_

namespace strap {

class Class;

namespace mckp {

template<typename PType, typename WType> class Problem;

namespace algorithm {

template<typename PType, typename WType>
void lp_dominate(const Problem<PType, WType>& problem, Class& klass);

} // namespace algorithm
} // namespace mckp
} // namespace strap

#endif
