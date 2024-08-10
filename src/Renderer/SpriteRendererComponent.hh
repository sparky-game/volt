#pragma once

#include "Sprite.hh"

namespace volt::renderer {
  struct SpriteRendererComponent {
    static inline auto cmp_name { "SpriteRenderer" };
    Sprite sprite;
    // Vector2<int32_t> position;
    int32_t position_x, position_y;
    SpriteRendererComponent(Sprite &&s) noexcept;
    void DrawDetails(void);
  };
}
