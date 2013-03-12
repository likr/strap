#include <algorithm>
#include <iterator>
#include "class.hpp"

namespace strap {

Class::Class(const int i, const int k_i)
  : i_(i), js_(k_i)
{
  for (int j = 0; j < k_i; ++j) {
    js_[j] = j;
  }
}


void Class::filter(const std::function<bool (int)>& pred)
{
  js_.resize(
      std::distance(
        js_.begin(),
        std::remove_if(
          js_.begin(),
          js_.end(),
          pred)));
}

} // namespace strap
