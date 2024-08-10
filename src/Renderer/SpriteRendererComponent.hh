#pragma once

#include "Sprite.hh"

namespace volt::renderer {
  struct SpriteRendererComponent {
    Sprite sprite;
    // Vector2<int32_t> position;
    int32_t position_x, position_y;
    SpriteRendererComponent(Sprite &&s) noexcept;
    void DrawDetails(void);
  };
}
