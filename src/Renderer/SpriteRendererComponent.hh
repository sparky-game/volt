#pragma once

#include "Sprite.hh"
#include "../Core/Vector2.hh"
#include "../Runtime/IComponent.hh"

namespace volt::renderer {
  struct SpriteRendererComponent : public runtime::IComponent {
    static inline auto cmp_name { "SpriteRenderer" };
    Sprite sprite;
    core::Vector2<float> position;
    float rotation;
    float scale;
    SpriteRendererComponent(Sprite &&s) noexcept;
    void Serialize(YAML::Emitter &out) final;
    bool Deserialize(YAML::Node &in) final;
    void Draw(void) final;
  };
}
