#ifndef STRAP_COMMON_CORE_CONSTRAINT_INDEXED_DATA_HPP_
#define STRAP_COMMON_CORE_CONSTRAINT_INDEXED_DATA_HPP_

#include <vector>

namespace strap {

template<typename T>
class ConstraintIndexedData
{
public:
  ConstraintIndexedData();
  ConstraintIndexedData(const int d);
  ConstraintIndexedData(const int d, const T& init);

  int d() const;
  T& get(const int k);
  const T& get(const int k) const;

private:
  std::vector<T> data_;
};

} // namespace strap

#include "constraint_indexed_data-inl.hpp"
#endif /* end of include guard */
