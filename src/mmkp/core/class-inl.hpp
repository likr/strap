#ifndef STRAP_MMKP_CORE_CLASS_INL_HPP_
#define STRAP_MMKP_CORE_CLASS_INL_HPP_

#include "class.hpp"

namespace strap {
namespace mmkp {

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


inline Class::JIterator Class::begin() const
{
  return js_.begin();
}


inline Class::JIterator Class::end() const
{
  return js_.end();
}

} // namespace mmkp
} // namespace strap

#endif
