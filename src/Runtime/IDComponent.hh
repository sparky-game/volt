#pragma once

#include "IComponent.hh"
#include "../Core/SnowflakeID.hh"

namespace volt::runtime {
  struct IDComponent : public IComponent {
    core::SnowflakeID id;
    IDComponent(core::SnowflakeID i);
    void Serialize(YAML::Emitter &) final;
    bool Deserialize(YAML::Node &) final;
    void Draw(void) final;
  };
}
