#pragma once

#include <memory>
#include "IComponent.hh"
#include "IBehaviour.hh"
#include "../Core/LogSystem.hh"

namespace volt::runtime {
  template <IBehaviour_t T>
  inline constexpr std::unique_ptr<T> Instantiate(void) {
    auto ptr { std::make_unique<T>() };
    // NOTE: `typeid(T).name()` is mangled
    VOLT_LOG_INFO("Behaviour instantiated [{}|{}]", fmt::ptr(ptr.get()), typeid(T).name());
    return ptr;
  }

  struct BehaviourComponent : public IComponent {
    std::unique_ptr<IBehaviour> behaviour { nullptr };
    BehaviourComponent(std::unique_ptr<IBehaviour> &&b);
    void Serialize(YAML::Emitter &) final;
    bool Deserialize(YAML::Node &) final;
    void Draw(void) final;
  };
}
