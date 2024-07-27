#include "Abs.hh"

namespace volt::core {
  [[maybe_unused]] static consteval void tests(void) {
    static_assert(Abs(7) == 7);
    static_assert(Abs(5.5f) == 5.5f);
    static_assert(Abs(5.5) == 5.5);
    static_assert(Abs(-7) == 7);
    static_assert(Abs(-5.5f) == 5.5f);
    static_assert(Abs(-5.5) == 5.5);
  }
}
