#ifndef STRAP_COMMON_CORE_INDEX_HPP_
#define STRAP_COMMON_CORE_INDEX_HPP_

#include <vector>
#include "class.hpp"

namespace strap {

class Index
{
public:
  typedef std::vector<Class>::const_iterator ClassIterator;
  template<typename KInputIterator>
  Index(const KInputIterator k_first, const KInputIterator k_last);
  int size() const;
  ClassIterator begin() const;
  ClassIterator end() const;
  const Class& at(const int i_index) const;


private:
  std::vector<Class> classes_;
};

} // namespace strap

#include "index-inl.hpp"
#endif