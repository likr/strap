#include "constraint_index.hpp"


namespace strap {

ConstraintIndex::ConstraintIndex(const int d)
  : index_(d)
{
  for (int k = 0; k < d; ++k) {
    index_[k] = k;
  }
}

}
