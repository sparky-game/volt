#include "Sqrt.hh"
#include "Vector2.hh"

namespace volt::core {
  template <typename T>
  constexpr Vector2<T>::Vector2(T x, T y) noexcept : m_x{x}, m_y{y} {}

  template <typename T>
  constexpr T Vector2<T>::Dot(const Vector2 &v) const noexcept {
    return (m_x * v.m_x) + (m_y * v.m_y);
  }

  template <typename T>
  constexpr T Vector2<T>::LengthSquared(void) const noexcept {
    return Dot(*this);
  }

  template <typename T>
  constexpr T Vector2<T>::Length(void) const noexcept {
    return Sqrt(LengthSquared());
  }

  template <typename T>
  constexpr Vector2<T> Vector2<T>::Normalize(void) const noexcept {
    T len { Length() };
    if (not len) return *this;
    return *this / len;
  }

  template <typename T>
  constexpr T Vector2<T>::Dot(const Vector2 &u, const Vector2 &v) noexcept {
    return u.Dot(v);
  }

  template <typename T>
  constexpr Vector2<T> Vector2<T>::operator+(const Vector2 &v) const noexcept {
    return {
      m_x + v.m_x,
      m_y + v.m_y
    };
  }

  template <typename T>
  constexpr Vector2<T> Vector2<T>::operator-(const Vector2 &v) const noexcept {
    return *this + (-1 * v);
  }

  template <typename T>
  constexpr T Vector2<T>::operator*(const Vector2 &v) const noexcept {
    return Dot(v);
  }

  template <typename T>
  constexpr Vector2<T> Vector2<T>::operator*(const T s) const noexcept {
    return {
      m_x * s,
      m_y * s
    };
  }

  template <typename T>
  constexpr Vector2<T> Vector2<T>::operator/(const T s) const noexcept {
    return {
      m_x / s,
      m_y / s
    };
  }

  [[maybe_unused]] static consteval void tests(void) {
    constexpr Vector2<> a{0, 1}, b{1, 0};
    static_assert(a < b);
    static_assert(not (a > b));
    static_assert(a != b);
    static_assert(not (a == b));
    static_assert(a == a);
    static_assert(a + Vector2<>::zero() == a);
    static_assert(Vector2<>::zero() + a == a);
    static_assert(b + Vector2<>::one() == Vector2<>{2, 1});
    static_assert(Vector2<>::one() + b == Vector2<>{2, 1});
    static_assert(a + b == Vector2<>{1, 1});
    static_assert(a - b == Vector2<>{-1, 1});
    static_assert(a.Dot(b) == 0);
    static_assert(Vector2<>::Dot(a, b) == 0);
    static_assert(a * b == 0);
    static_assert(5 * a == Vector2<>{0, 5});
    static_assert(b * -2 == Vector2<>{-2, 0});
    static_assert(a.LengthSquared() == 1);
    // NOTE: in C++20, the standard does not guarantee std::sqrt being constexpr.
    // clang's builtin for std::sqrt (`__builtin_sqrt`) is not constexpr, but
    // gcc's is.
    // until C++26, the standard will not guarantee std::sqrt being constexpr; so
    // the best solution is to make our own constexpr sqrt implementation.
    static_assert(a.Length() == Sqrt(1.0f));
    static_assert(Vector2<>::zero().Normalize() == Vector2<>::zero());
    static_assert(Vector2<>::right().Normalize() == Vector2<>::right());
    static_assert(Vector2<>::up().Normalize() == Vector2<>::up());
  }
}
