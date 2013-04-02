#ifndef STRAP_MCKP_CORE_PROBLEM_HPP_
#define STRAP_MCKP_CORE_PROBLEM_HPP_

#include <vector>

namespace strap {

template<typename T> class IndexedData;
namespace mckp {

template<typename PType, typename WType>
class Problem
{
public:
  template<typename KInputIterator>
  Problem(const KInputIterator k_first, const KInputIterator k_last);
  int m() const;
  int n() const;
  int k(const int i) const;
  const PType& p(const int i, const int j) const;
  PType& p(const int i, const int j);
  const WType& w(const int i, const int j) const;
  WType& w(const int i, const int j);
  const WType& c() const;
  WType& c();
  template<typename T> IndexedData<T>* data(const T init) const;


private:
  std::vector<int> k_;
  std::vector<int> offset_;
  std::vector<PType> p_;
  std::vector<WType> w_;
  WType c_;
  int m_;
  int n_;
};

} // namespace mckp
} // namespace strap

#include "problem-inl.hpp"
#endif
