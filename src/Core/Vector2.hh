#pragma once

#include <string>
#include <compare>
#include "LogSystem.hh"

namespace volt::core {
  template <typename T = float>
  class Vector2 {
    T m_x, m_y;
  public:
    constexpr Vector2(void) = default;
    inline constexpr Vector2(T x, T y) noexcept : m_x{x}, m_y{y} {}
    inline constexpr T X(void) const noexcept { return m_x; }
    inline constexpr void X(T x) noexcept     { m_x = x;    }
    inline constexpr T Y(void) const noexcept { return m_y; }
    inline constexpr void Y(T y) noexcept     { m_y = y;    }
    /**
     * @brief Adds two vectors together.
     * @param v The second vector to add.
     * @return The summed vector.
     */
    inline constexpr Vector2 Add(const Vector2 &v) const noexcept {
      return {
        m_x + v.m_x,
        m_y + v.m_y
      };
    }
    /**
     * @brief Restricts a vector between a minimum and a maximum value.
     * @param min The minimum value.
     * @param max The maximum value.
     */
    inline constexpr void Clamp(const Vector2 &min, const Vector2 &max) noexcept {
      *this = Clamp(*this, min, max);
    }
    constexpr T Dot(const Vector2 &v) const noexcept;
    constexpr T LengthSquared(void) const noexcept;
    constexpr T Length(void) const noexcept;
    constexpr Vector2 Normalize(void) const noexcept;
    /**
     * @brief Returns the string representation of the vector using default formatting.
     * @return The string representation of the vector.
     */
    inline constexpr std::string ToString(void) const noexcept {
      return fmt::format("({:.3f}, {:.3f})", m_x, m_y);
    }
    /**
     * @brief Restricts a vector between a minimum and a maximum value.
     * @param v The vector to restrict.
     * @param min The minimum value.
     * @param max The maximum value.
     * @return The restricted vector.
     */
    static inline constexpr Vector2 Clamp(const Vector2 &v, const Vector2 &min, const Vector2 &max) noexcept {
      return Min(Max(v, min), max);
    }
    static constexpr T Dot(const Vector2 &u, const Vector2 &v) noexcept;
    /**
     * @brief Returns a vector whose elements are the maximum of each of the pairs of elements in two specified vectors.
     * @param u The first vector.
     * @param v The second vector.
     * @return The maximized vector.
     */
    static inline constexpr Vector2 Max(const Vector2 &u, const Vector2 &v) noexcept {
      return {
        u.m_x > v.m_x ? u.m_x : v.m_x,
        u.m_y > v.m_y ? u.m_y : v.m_y
      };
    }
    /**
     * @brief Returns a vector whose elements are the minimum of each of the pairs of elements in two specified vectors.
     * @param u The first vector.
     * @param v The second vector.
     * @return The minimized vector.
     */
    static inline constexpr Vector2 Min(const Vector2 &u, const Vector2 &v) noexcept {
      return {
        u.m_x < v.m_x ? u.m_x : v.m_x,
        u.m_y < v.m_y ? u.m_y : v.m_y
      };
    }
    static inline constexpr Vector2 zero(void)  noexcept { return {0, 0};  }
    static inline constexpr Vector2 left(void)  noexcept { return {-1, 0}; }
    static inline constexpr Vector2 right(void) noexcept { return {1, 0};  }
    static inline constexpr Vector2 down(void)  noexcept { return {0, -1}; }
    static inline constexpr Vector2 up(void)    noexcept { return {0, 1};  }
    static inline constexpr Vector2 one(void)   noexcept { return {1, 1};  }
    constexpr auto operator<=>(const Vector2 &) const noexcept = default;
    inline constexpr Vector2 operator+(const Vector2 &v) const noexcept { return Add(v); }
    inline constexpr void operator+=(const Vector2 &v) noexcept { *this = *this + v; }
    constexpr Vector2 operator-(const Vector2 &v) const noexcept;
    constexpr T operator*(const Vector2 &v) const noexcept;
    constexpr Vector2 operator*(const T s) const noexcept;
    constexpr Vector2 operator/(const T s) const noexcept;
    friend inline constexpr Vector2 operator*(const T s, const Vector2 &v) noexcept { return v * s; }
    friend inline constexpr Vector2 operator/(const T s, const Vector2 &v) noexcept { return v / s; }
  };
}
