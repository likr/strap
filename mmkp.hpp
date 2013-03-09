#ifndef STRAP_CORE_MMKP_H_
#define STRAP_CORE_MMKP_H_

#include <vector>

namespace strap {

template<typename PType, typename WType>
class Item
{

public:
  typedef const WType* WRandomAccessIterator;

  class W
  {
  public:
    W(Item& item);
    const WRandomAccessIterator begin() const;
    const WRandomAccessIterator end() const;
  private:
    Item& item_;
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


template<typename PType, typename WType> 
class Problem
{
public:
  typedef const WType* CRandomAccessIterator;
  Problem(const std::vector<int>& k, const int d);
  int m() const;
  int n() const;
  int d() const;
  int k(const int i) const;
  const PType& p(const int i, const int j) const;
  PType& p(const int i, const int j);
  const WType& w(const int i, const int j, const int k) const;
  WType& w(const int i, const int j, const int k);
  const WType& c(const int k) const;
  WType& c(const int k);
  const CRandomAccessIterator c_begin() const;
  const CRandomAccessIterator c_end() const;
  Item<PType, WType> item(const int i, const int j) const;


private:
  std::vector<int> k_;
  std::vector<int> offset_;
  std::vector<WType> c_;
  std::vector<PType> p_;
  std::vector<WType> w_;
  int m_;
  int n_;
  int d_;
};

} // namespace strap

#include "mmkp.impl"
#endif
