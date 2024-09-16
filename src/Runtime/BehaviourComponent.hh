#pragma once

#include <memory>
#include "IBehaviour.hh"

namespace volt::runtime {
  template <typename T>
  inline constexpr std::unique_ptr<T> Instantiate(void) {
    auto ptr { std::make_unique<T>() };
    // NOTE: `typeid(T).name()` is mangled
    VOLT_LOG_INFO("Behaviour instantiated [{}|{}]", fmt::ptr(ptr.get()), typeid(T).name());
    return ptr;
  }

  struct BehaviourComponent {
    std::unique_ptr<IBehaviour> behaviour { nullptr };
  };
}
