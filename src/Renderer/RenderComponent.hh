#pragma once

#include "ISprite.hh"

namespace volt::renderer {
  struct RenderComponent {
    ISprite *sprite { nullptr };
    // Vector2<int32_t> position;
    int32_t position_x, position_y;
    RenderComponent(ISprite *s) : sprite{s} {}
  };
}
