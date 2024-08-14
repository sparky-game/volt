#pragma once

#include "Sprite.hh"
#include "../Core/Vector2.hh"

namespace YAML {
  class Emitter;
  class Node;
}

namespace volt::renderer {
  struct SpriteRendererComponent {
    static inline auto cmp_name { "SpriteRenderer" };
    Sprite sprite;
    core::Vector2<int32_t> position;
    SpriteRendererComponent(Sprite &&s) noexcept;
    void Serialize(YAML::Emitter &out);
    bool Deserialize(YAML::Node &in);
    void DrawDetails(void);
  };
}
