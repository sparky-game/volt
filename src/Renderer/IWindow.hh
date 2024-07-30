#pragma once

#include <memory>
#include <cstdint>
#include "ISprite.hh"

namespace volt::renderer {
  struct IWindow {
    virtual ~IWindow(void) = default;
    virtual bool IsOpen(void) const = 0;
    virtual void Clear(uint32_t color) = 0;
    virtual void Draw(const ISprite *s, uint32_t x, uint32_t y) = 0;
    virtual void Update(void) = 0;
  };
}
