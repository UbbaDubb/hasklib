#pragma once
#include <cstddef>
#include <vector>

namespace hasklib::core {

// Project-wide numeric aliases. Centralising these means a future switch
// (e.g. to float, or a custom dual number for autodiff) touches one file.
using Real = double;
using Size = std::size_t;
using Vector = std::vector<Real>;

}  // namespace hasklib::core