#include "BehaviourComponent.hh"

namespace volt::runtime {
  BehaviourComponent::BehaviourComponent(std::unique_ptr<IBehaviour> &&b)
    : behaviour{std::move(b)}
  {}

  void BehaviourComponent::Serialize(YAML::Emitter &) {}

  bool BehaviourComponent::Deserialize(YAML::Node &) {
    return false;
  }

  void BehaviourComponent::Draw(void) {}
}
