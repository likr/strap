#ifndef STRAP_MMKP_CORE_ITEM_HPP_
#define STRAP_MMKP_CORE_ITEM_HPP_

namespace strap {
namespace mmkp {

template<typename PType, typename WType>
class Item
{

public:
  typedef const WType* WRandomAccessIterator;

  class W
  {
  public:
    W(const Item& item);
    const WRandomAccessIterator begin() const;
    const WRandomAccessIterator end() const;
  private:
    const Item& item_;
  };

  Item(const PType* p, const WType* w, const int d);
  const PType& p() const;
  W w() const;
  const WType& w(const int k) const;
  const WRandomAccessIterator w_begin() const;
  const WRandomAccessIterator w_end() const;


private:
  const PType* p_;
  const WType* w_;
  int d_;
};

} // namespace mmkp  
} // namespace strap

#include "item-inl.hpp"
#endif
