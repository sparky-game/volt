#include "Sqrt.hh"
#include "Vector3.hh"

namespace volt::core {
  template <typename T>
  constexpr Vector3<T>::Vector3(T x, T y, T z) noexcept : m_x{x}, m_y{y}, m_z{z} {}

  template <typename T>
  constexpr T Vector3<T>::Dot(const Vector3 &v) const noexcept {
    return (m_x * v.m_x) + (m_y * v.m_y) + (m_z * v.m_z);
  }

  template <typename T>
  constexpr T Vector3<T>::LengthSquared(void) const noexcept {
    return Dot(*this);
  }

  template <typename T>
  constexpr T Vector3<T>::Length(void) const noexcept {
    return Sqrt(LengthSquared());
  }

  template <typename T>
  constexpr Vector3<T> Vector3<T>::Normalize(void) const noexcept {
    T len { Length() };
    if (not len) return *this;
    return *this / len;
  }

  template <typename T>
  constexpr Vector3<T> Vector3<T>::Cross(const Vector3 &v) const noexcept {
    return {
      (m_y * v.m_z) - (m_z * v.m_y),
      (m_z * v.m_x) - (m_x * v.m_z),
      (m_x * v.m_y) - (m_y * v.m_x)
    };
  }

  template <typename T>
  constexpr T Vector3<T>::Dot(const Vector3 &u, const Vector3 &v) noexcept {
    return u.Dot(v);
  }

  template <typename T>
  constexpr Vector3<T> Vector3<T>::operator+(const Vector3 &v) const noexcept {
    return {
      m_x + v.m_x,
      m_y + v.m_y,
      m_z + v.m_z
    };
  }

  template <typename T>
  constexpr Vector3<T> Vector3<T>::operator-(const Vector3 &v) const noexcept {
    return *this + (-1 * v);
  }

  template <typename T>
  constexpr T Vector3<T>::operator*(const Vector3 &v) const noexcept {
    return Dot(v);
  }

  template <typename T>
  constexpr Vector3<T> Vector3<T>::operator*(const T s) const noexcept {
    return {
      m_x * s,
      m_y * s,
      m_z * s
    };
  }

  template <typename T>
  constexpr Vector3<T> Vector3<T>::operator/(const T s) const noexcept {
    return {
      m_x / s,
      m_y / s,
      m_z / s
    };
  }

  [[maybe_unused]] static consteval void tests(void) {
    constexpr Vector3<> a{0, 1, 1}, b{1, 1, 0};
    static_assert(a < b);
    static_assert(not (a > b));
    static_assert(a != b);
    static_assert(not (a == b));
    static_assert(a == a);
    static_assert(a + Vector3<>::zero() == a);
    static_assert(Vector3<>::zero() + a == a);
    static_assert(b + Vector3<>::one() == Vector3<>{2, 2, 1});
    static_assert(Vector3<>::one() + b == Vector3<>{2, 2, 1});
    static_assert(a + b == Vector3<>{1, 2, 1});
    static_assert(a - b == Vector3<>{-1, 0, 1});
    static_assert(a.Dot(b) == 1);
    static_assert(Vector3<>::Dot(a, b) == 1);
    static_assert(a * b == 1);
    static_assert(5 * a == Vector3<>{0, 5, 5});
    static_assert(b * -2 == Vector3<>{-2, -2, 0});
    static_assert(a.LengthSquared() == 2);
    // NOTE: in C++20, the standard does not guarantee std::sqrt being constexpr.
    // clang's builtin for std::sqrt (`__builtin_sqrt`) is not constexpr, but
    // gcc's is.
    // until C++26, the standard will not guarantee std::sqrt being constexpr; so
    // the best solution is to make our own constexpr sqrt implementation.
    static_assert(a.Length() == Sqrt(2.0f));
    static_assert(Vector3<>::zero().Normalize() == Vector3<>::zero());
    static_assert(Vector3<>::right().Normalize() == Vector3<>::right());
    static_assert(Vector3<>::up().Normalize() == Vector3<>::up());
    static_assert(Vector3<>::forward().Normalize() == Vector3<>::forward());
    static_assert(a.Cross(b) == Vector3<>{-1, 1, -1});
    static_assert(a * a.Cross(b) == 0);
    static_assert(b * a.Cross(b) == 0);
  }
}
