#include <csignal>
#include "Goodbye.hh"

namespace volt::app {
  void Goodbye::goodbye(int) noexcept {
    s_goodbyeToggle = true;
  }

  void Goodbye::Init(void) {
    std::signal(SIGINT, goodbye);
  }
}
