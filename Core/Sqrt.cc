#include "Sqrt.hh"

namespace volt::core {
  [[maybe_unused]] static consteval void tests(void) {
    static_assert(Sqrt(4) == 2);
    static_assert(Sqrt(4.0f) == 2.0f);
    static_assert(Sqrt(4.0) == 2.0);
    static_assert(Sqrt(2) == 1);
    static_assert(Sqrt(2.0f) == 1.4142135f);
    static_assert(Sqrt(2.0) == 1.4142135623730949);
  }
}
