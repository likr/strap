#ifndef STRAP_MMKP_CORE_INDEX_INL_HPP_
#define STRAP_MMKP_CORE_INDEX_INL_HPP_

#include <iterator>
#include "class.hpp"
#include "index.hpp"

namespace strap {
namespace mmkp {
  
template<typename KInputIterator>
Index::Index(const KInputIterator k_first, const KInputIterator k_last)
{
  int i = 0;
  std::transform(
      k_first, k_last,
      std::back_inserter(classes_),
      [&i](const int k_i) {
        return Class(i++, k_i);
      });
}


inline int Index::size() const
{
  return classes_.size();
}


inline Index::ClassIterator Index::begin() const
{
  return classes_.begin();
}


inline Index::ClassIterator Index::end() const
{
  return classes_.end();
}


inline const Class& Index::at(const int i_index) const
{
  return classes_[i_index];
}

} // namespace mmkp
} // namespace strap

#endif
