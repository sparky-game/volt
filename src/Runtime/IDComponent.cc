#include "IDComponent.hh"

namespace volt::runtime {
  IDComponent::IDComponent(core::SnowflakeID i)
    : id{i}
  {}

  void IDComponent::Serialize(YAML::Emitter &) {}

  bool IDComponent::Deserialize(YAML::Node &) {
    return false;
  }

  void IDComponent::Draw(void) {}
}
