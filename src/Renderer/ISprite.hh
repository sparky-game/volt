#pragma once

#include <cstdint>

namespace volt::renderer {
  struct ISprite {
    virtual ~ISprite(void) = default;
    virtual uint32_t width(void) const = 0;
    virtual uint32_t height(void) const = 0;
    virtual const void *data(void) const = 0;
  };
}
