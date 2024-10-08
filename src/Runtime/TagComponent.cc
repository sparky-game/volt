#include "TagComponent.hh"

namespace volt::runtime {
  TagComponent::TagComponent(const std::string &t)
    : tag{t}
  {}

  void TagComponent::Serialize(YAML::Emitter &) {}

  bool TagComponent::Deserialize(YAML::Node &) {
    return false;
  }

  void TagComponent::Draw(void) {}
}
