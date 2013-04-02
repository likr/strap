#ifndef STRAP_COMMON_CORE_INDEX_HPP_
#define STRAP_COMMON_CORE_INDEX_HPP_

#include <functional>
#include <vector>

namespace strap {

class Class;


class Index
{
public:
  typedef std::vector<Class>::iterator ClassIterator;
  typedef std::vector<Class>::const_iterator ClassConstIterator;
  template<typename KInputIterator>
  Index(const KInputIterator k_first, const KInputIterator k_last);
  int size() const;
  ClassIterator begin();
  ClassConstIterator begin() const;
  ClassIterator end();
  ClassConstIterator end() const;
  const Class& at(const int i_index) const;
  void each(const std::function<void (Class&)>& f);
  void each(const std::function<void (const Class&)>& f) const;
  void remove_if(const std::function<bool (const Class&)>& pred);
  void sort(const std::function<bool (const Class&, const Class&)>& cmp);


private:
  std::vector<Class> classes_;
};

} // namespace strap

#include "index-inl.hpp"
#endif
