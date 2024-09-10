#pragma once

#include <atomic>

namespace volt::app {
  class Goodbye {
    static inline volatile std::atomic<bool> s_goodbyeToggle { false };
    static void goodbye(int) noexcept;
  public:
    static void Init(void);
    static inline const std::atomic<bool> IsAlive(void) noexcept { return not s_goodbyeToggle; }
  };
}
