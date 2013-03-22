#ifndef STRAP_COMMON_CORE_CONSTRAINT_INDEX_HPP_
#define STRAP_COMMON_CORE_CONSTRAINT_INDEX_HPP_

#include <vector>

namespace strap {

class ConstraintIndex
{
public:
  typedef std::vector<int>::iterator Iterator;
  typedef std::vector<int>::const_iterator ConstIterator;

  ConstraintIndex(const int d);

  Iterator begin();
  ConstIterator begin() const;
  Iterator end();
  ConstIterator end() const;


private:
  std::vector<int> index_;
};

} // namespace strap

#include "constraint_index-inl.hpp"
#endif /* end of include guard */
