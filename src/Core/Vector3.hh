#pragma once

#include <compare>

namespace volt::core {
  template <typename T = float>
  class Vector3 {
    T m_x, m_y, m_z;
  public:
    constexpr Vector3(void) = default;
    inline constexpr Vector3(T x, T y, T z) noexcept : m_x{x}, m_y{y}, m_z{z} {}
    inline constexpr T X(void) const noexcept { return m_x; }
    inline constexpr void X(T x) noexcept { m_x = x; }
    inline constexpr T Y(void) const noexcept { return m_y; }
    inline constexpr void Y(T y) noexcept { m_y = y; }
    inline constexpr T Z(void) const noexcept { return m_z; }
    inline constexpr void Z(T z) noexcept { m_z = z; }
    constexpr T Dot(const Vector3 &v) const noexcept;
    constexpr T LengthSquared(void) const noexcept;
    constexpr T Length(void) const noexcept;
    constexpr Vector3 Normalize(void) const noexcept;
    constexpr Vector3 Cross(const Vector3 &v) const noexcept;
    static constexpr T Dot(const Vector3 &u, const Vector3 &v) noexcept;
    static inline constexpr Vector3 zero(void)    noexcept { return {0, 0, 0};  }
    static inline constexpr Vector3 left(void)    noexcept { return {-1, 0, 0}; }
    static inline constexpr Vector3 right(void)   noexcept { return {1, 0, 0};  }
    static inline constexpr Vector3 down(void)    noexcept { return {0, -1, 0}; }
    static inline constexpr Vector3 up(void)      noexcept { return {0, 1, 0};  }
    static inline constexpr Vector3 back(void)    noexcept { return {0, 0, -1}; }
    static inline constexpr Vector3 forward(void) noexcept { return {0, 0, 1};  }
    static inline constexpr Vector3 one(void)     noexcept { return {1, 1, 1};  }
    constexpr auto operator<=>(const Vector3 &) const noexcept = default;
    constexpr Vector3 operator+(const Vector3 &v) const noexcept;
    constexpr Vector3 operator-(const Vector3 &v) const noexcept;
    constexpr T operator*(const Vector3 &v) const noexcept;
    constexpr Vector3 operator*(const T s) const noexcept;
    constexpr Vector3 operator/(const T s) const noexcept;
    friend inline constexpr Vector3 operator*(const T s, const Vector3 &v) noexcept { return v * s; }
    friend inline constexpr Vector3 operator/(const T s, const Vector3 &v) noexcept { return v / s; }
  };
}
