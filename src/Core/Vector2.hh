#pragma once

#include <compare>

namespace volt::core {
  template <typename T = float>
  class Vector2 {
    T m_x, m_y;
  public:
    constexpr Vector2(T x, T y) noexcept;
    constexpr T Dot(const Vector2 &v) const noexcept;
    constexpr T LengthSquared(void) const noexcept;
    constexpr T Length(void) const noexcept;
    constexpr Vector2 Normalize(void) const noexcept;
    static constexpr T Dot(const Vector2 &u, const Vector2 &v) noexcept;
    static inline constexpr Vector2 zero(void)  noexcept { return {0, 0};  }
    static inline constexpr Vector2 left(void)  noexcept { return {-1, 0}; }
    static inline constexpr Vector2 right(void) noexcept { return {1, 0};  }
    static inline constexpr Vector2 down(void)  noexcept { return {0, -1}; }
    static inline constexpr Vector2 up(void)    noexcept { return {0, 1};  }
    static inline constexpr Vector2 one(void)   noexcept { return {1, 1};  }
    constexpr auto operator<=>(const Vector2 &) const noexcept = default;
    constexpr Vector2 operator+(const Vector2 &v) const noexcept;
    constexpr Vector2 operator-(const Vector2 &v) const noexcept;
    constexpr T operator*(const Vector2 &v) const noexcept;
    constexpr Vector2 operator*(const T s) const noexcept;
    constexpr Vector2 operator/(const T s) const noexcept;
    friend inline constexpr Vector2 operator*(const T s, const Vector2 &v) noexcept { return v * s; }
    friend inline constexpr Vector2 operator/(const T s, const Vector2 &v) noexcept { return v / s; }
  };
}
