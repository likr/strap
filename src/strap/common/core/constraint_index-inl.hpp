#ifndef STRAP_COMMON_CORE_CONSTRAINT_INDEX_INL_HPP_
#define STRAP_COMMON_CORE_CONSTRAINT_INDEX_INL_HPP_

#include "constraint_index.hpp"

namespace strap {

inline ConstraintIndex::Iterator ConstraintIndex::begin()
{
  return index_.begin();
}


inline ConstraintIndex::ConstIterator ConstraintIndex::begin() const
{
  return index_.begin();
}


inline ConstraintIndex::Iterator ConstraintIndex::end()
{
  return index_.end();
}


inline ConstraintIndex::ConstIterator ConstraintIndex::end() const
{
  return index_.end();
}

} // namespace strap

#endif /* end of include guard */
