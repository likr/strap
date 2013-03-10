#ifndef STRAP_MMKP_CORE_CLASS_HPP_
#define STRAP_MMKP_CORE_CLASS_HPP_

#include <vector>

namespace strap {
namespace mmkp {

class Class
{
public:
  typedef std::vector<int>::const_iterator JIterator;
  Class(const int i, const int k_i);
  template<typename JInputIterator>
  Class(
      const int i,
      const JInputIterator j_first,
      const JInputIterator j_last);
  int i() const;
  JIterator begin() const;
  JIterator end() const;


private:
  int i_;
  std::vector<int> js_;
};

} // namespace mmkp
} // namespace strap

#include "class-inl.hpp"
#endif
