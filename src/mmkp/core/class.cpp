#include "class.hpp"

namespace strap {
namespace mmkp {

Class::Class(const int i, const int k_i)
  : i_(i), js_(k_i)
{
  for (int j = 0; j < k_i; ++j) {
    js_[j] = j;
  }
}

} // namespace mmkp
} // namespace strap
