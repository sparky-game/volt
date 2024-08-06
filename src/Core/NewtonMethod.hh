#pragma once

namespace volt::core {
  template <typename T = float>
  inline constexpr T NewtonMethod(T x, T curr, T prev) noexcept {
    return curr == prev ? curr : NewtonMethod<T>(x, 0.5f * (curr + x / curr), curr);
  }
}
