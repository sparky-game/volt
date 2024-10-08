#pragma once

#include <string>
#include "IComponent.hh"

namespace volt::runtime {
  struct TagComponent : public IComponent {
    std::string tag;
    TagComponent(const std::string &t);
    void Serialize(YAML::Emitter &) final;
    bool Deserialize(YAML::Node &) final;
    void Draw(void) final;
  };
}
