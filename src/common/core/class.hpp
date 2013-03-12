#ifndef STRAP_COMMON_CORE_CLASS_HPP_
#define STRAP_COMMON_CORE_CLASS_HPP_

#include <functional>
#include <vector>

namespace strap {

class Class
{
public:
  typedef std::vector<int>::iterator JIterator;
  typedef std::vector<int>::const_iterator JConstIterator;
  Class(const int i, const int k_i);
  template<typename JInputIterator>
  Class(
      const int i,
      const JInputIterator j_first,
      const JInputIterator j_last);
  int i() const;
  int size() const;
  JConstIterator begin() const;
  JIterator begin();
  JConstIterator end() const;
  JIterator end();
  void filter(const std::function<bool (int)>& pred);


private:
  int i_;
  std::vector<int> js_;
};

} // namespace strap

#include "class-inl.hpp"
#endif
