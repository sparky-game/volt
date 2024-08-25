#pragma once

#include "IComponent.hh"
#include "../Core/Vector2.hh"

namespace volt::runtime {
  struct TransformComponent : public IComponent {
    static inline auto cmp_name { "Transform" };
    core::Vector2<float> position;
    TransformComponent(void);
    TransformComponent(float pos_x, float pos_y);
    void Serialize(YAML::Emitter &out) final;
    bool Deserialize(YAML::Node &in) final;
    void Draw(void) final;
  };
}
