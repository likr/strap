#ifndef STRAP_COMMON_CORE_INDEXED_DATA_HPP_
#define STRAP_COMMON_CORE_INDEXED_DATA_HPP_

#include <vector>

namespace strap {

template<typename T>
class IndexedData
{
public:
  IndexedData();
  template<typename KInputIterator>
  IndexedData(const KInputIterator k_first, const KInputIterator k_last);
  template<typename KInputIterator>
  IndexedData(const KInputIterator k_first, const KInputIterator k_last, const T& init);

  int m() const;
  int n() const;
  T& get(const int i, const int j);
  const T& get(const int i, const int j) const;


private:
  std::vector<int> offset_;
  std::vector<T> data_;
};

} // namespace strap

#include "indexed_data-inl.hpp"
#endif /* end of include guard */
