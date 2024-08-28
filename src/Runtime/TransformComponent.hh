#pragma once

#include "IComponent.hh"
#include "../Core/Vector2.hh"

namespace volt::runtime {
  struct TransformComponent : public IComponent {
    static inline auto cmp_name { "Transform" };
    core::Vector2<float> position;
    float rotation;
    float scale;
    TransformComponent(const core::Vector2<float> &p = core::Vector2<>::zero(), float r = 0, float s = 1);
    void Serialize(YAML::Emitter &out) final;
    bool Deserialize(YAML::Node &in) final;
    void Draw(void) final;
  };
}
