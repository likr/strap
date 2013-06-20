#include <iostream>
#include <algorithm>
#include <functional>
#include <iterator>
#include "class.hpp"
#include "index.hpp"

namespace strap {

Index::Index()
{
}


void Index::each(const std::function<void (Class&)>& f)
{
  std::for_each(
      classes_.begin(),
      classes_.end(),
      f);
}


void Index::remove_if(const std::function<bool (const Class&)>& pred)
{
  classes_.resize(
      std::distance(
        classes_.begin(),
        std::remove_if(
          classes_.begin(),
          classes_.end(),
          pred)));
}


void Index::sort(const std::function<bool (const Class&, const Class&)>& cmp)
{
  std::sort(
      classes_.begin(),
      classes_.end(),
      cmp);
}


void Index::traverse(const std::function<bool (const int, const int, const int)>& on_node)
{
  const int m = size();
  std::vector<Class::const_iterator> j_iterators(m);
  int depth = 0;

  for (const auto& klass : *this) {
    const int i = klass.i();
    j_iterators[i] = klass.end();
  }
  while (depth >= 0) {
    const auto& klass = this->at(depth);
    const int i = klass.i();
    if (j_iterators[i] == klass.end()) {
      j_iterators[i] = klass.begin();
    }
    const int j = *j_iterators[i]++;
    if (on_node(depth, i, j) && depth < m - 1) {
      ++depth;
    } else {
      while (j_iterators[this->at(depth).i()] == this->at(depth).end() && depth >= 0) {
        --depth;
      }
    }
  }
}

} // namespace strap
