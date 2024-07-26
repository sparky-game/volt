#pragma once

#include <limits>
#include "NewtonMethod.hh"

namespace volt::core {
  template <typename T = float>
  inline constexpr T Sqrt(const T x) noexcept {
    return x >= 0 and x < std::numeric_limits<T>::infinity()
      ? NewtonMethod<T>(x, x, 0)
      : std::numeric_limits<T>::quiet_NaN();
  }

  template <>
  inline constexpr int Sqrt<int>(const int x) noexcept {
    return static_cast<int>(Sqrt(static_cast<float>(x)));
  }
}
