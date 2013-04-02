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

} // namespace strap
