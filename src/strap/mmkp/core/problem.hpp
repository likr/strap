#ifndef STRAP_MMKP_CORE_PROBLEM_HPP_
#define STRAP_MMKP_CORE_PROBLEM_HPP_

#include <iostream>
#include <vector>

namespace strap {

class Index;
class ConstraintIndex;
template<typename T> class IndexedData;
template<typename T> class ClassIndexedData;

namespace mmkp {

template<typename PType, typename WType> class Item;


template<typename PType, typename WType> 
class Problem
{
public:
  typedef const WType* CConstRandomAccessIterator;
  typedef WType* CRandomAccessIterator;

  Problem();
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
  CRandomAccessIterator c_begin();
  CConstRandomAccessIterator c_begin() const;
  CRandomAccessIterator c_end();
  CConstRandomAccessIterator c_end() const;
  PType& p_offset();
  const PType& p_offset() const;
  Item<PType, WType> item(const int i, const int j) const;
  Index index() const;
  ConstraintIndex constraint_index() const;
  template<typename T> IndexedData<T>* data(const T init) const;
  template<typename T> ClassIndexedData<T>* class_data(const T init) const;
  static Problem<PType, WType>* read(std::istream& in);


private:
  std::vector<int> k_;
  std::vector<int> offset_;
  std::vector<WType> c_;
  std::vector<PType> p_;
  std::vector<WType> w_;
  int m_;
  int n_;
  int d_;
  PType p_offset_;
};

} // namespace mmkp
} // namespace strap


template<typename PType, typename WType>
std::ostream& operator<<(
    std::ostream& out,
    const strap::mmkp::Problem<PType, WType>& problem);

#include "problem-inl.hpp"
#endif
