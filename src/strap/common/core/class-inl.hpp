#ifndef STRAP_COMMON_CORE_CLASS_INL_HPP_
#define STRAP_COMMON_CORE_CLASS_INL_HPP_

#include "class.hpp"

namespace strap {

template<typename JInputIterator>
Class::Class(
    const int i,
    const JInputIterator j_first,
    const JInputIterator j_last)
  : i_(i), js_(j_first, j_last)
{
}


inline int Class::i() const
{
  return i_;
}


inline int Class::size() const
{
  return js_.size();
}


inline Class::const_iterator Class::begin() const
{
  return js_.begin();
}


inline Class::iterator Class::begin()
{
  return js_.begin();
}


inline Class::const_iterator Class::end() const
{
  return js_.end();
}


inline Class::iterator Class::end()
{
  return js_.end();
}


inline int Class::operator[](const int index) const
{
  return js_[index];
}

} // namespace strap

#endif
