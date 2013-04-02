#ifndef STRAP_MMKP_ALGORITHM_LP_RELAXATION_HPP_
#define STRAP_MMKP_ALGORITHM_LP_RELAXATION_HPP_

#include <coin/ClpSimplex.hpp>

namespace strap {

class Index;

namespace mmkp {

template<typename PType, typename WType>
class Problem;

namespace algorithm {

typedef ClpSimplex LpRelaxationProblem;

template<typename PType, typename WType>
LpRelaxationProblem* lp_relaxation(
    const Problem<PType, WType>& problem,
    const Index& index);

} // namespace algorithm
} // namespace mmkp
} // namespace strap

#endif
