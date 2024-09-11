#pragma once

#include "Sprite.hh"
#include "../Core/Vector2.hh"
#include "../Runtime/IComponent.hh"

namespace volt::renderer {
  struct SpriteRendererComponent : public runtime::IComponent {
    static inline auto cmp_name { "SpriteRenderer" };
    Sprite sprite;
    uint32_t color;
    bool flipX { false }, flipY { false };
    core::Vector2<float> position;
    float rotation;
    float scale;
    SpriteRendererComponent(Sprite &&s, uint32_t c = 0xffffffff) noexcept;
    void Serialize(YAML::Emitter &out) final;
    bool Deserialize(YAML::Node &in) final;
    void Draw(void) final;
  };
}
