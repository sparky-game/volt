#pragma once

#include "Sprite.hh"

namespace volt::renderer {
  struct RenderComponent {
    Sprite sprite;
    // Vector2<int32_t> position;
    int32_t position_x, position_y;
    RenderComponent(const Sprite &s) : sprite{s} {}
  };
}
