#pragma once

#include "IComponent.hh"
#include "../Core/Vector2.hh"

namespace volt::runtime {
  struct Rigidbody2DComponent : public IComponent {
    static inline auto cmp_name { "Rigidbody2D" };
    core::Vector2<float> velocity;
    Rigidbody2DComponent(const core::Vector2<float> &v = core::Vector2<>::zero());
    void Serialize(YAML::Emitter &out) final;
    bool Deserialize(YAML::Node &in) final;
    void Draw(void) final;
  };
}
