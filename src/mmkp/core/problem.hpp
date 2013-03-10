#ifndef STRAP_MMKP_CORE_PROBLEM_HPP_
#define STRAP_MMKP_CORE_PROBLEM_HPP_

#include <vector>
#include "item.hpp"

namespace strap {
namespace mmkp {

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

} // namespace mmkp
} // namespace strap

#include "problem-inl.hpp"
#endif
