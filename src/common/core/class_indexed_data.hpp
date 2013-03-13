#ifndef STRAP_COMMON_CORE_CLASS_INDEXED_DATA_HPP_
#define STRAP_COMMON_CORE_CLASS_INDEXED_DATA_HPP_

#include <vector>

namespace strap {

template<typename T>
class ClassIndexedData
{
public:
  ClassIndexedData(const int m);

  int m() const;
  T& get(const int i);
  const T& get(const int i) const;

private:
  std::vector<T> data_;
};

} // namespace strap

#include "class_indexed_data-inl.hpp"
#endif /* end of include guard */
