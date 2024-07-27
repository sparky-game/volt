#pragma once

namespace volt::core {
  template <typename T = float>
  inline constexpr T Abs(const T x) noexcept {
    return x < 0 ? -x : x;
  }
}
