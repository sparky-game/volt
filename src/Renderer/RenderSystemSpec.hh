#pragma once

#include <string>
#include <cstdint>

namespace volt::renderer {
  struct RenderSystemSpec {
    uint32_t width, height;
    std::string name;
    uint32_t max_fps;
    bool is_editor { false };
  };
}
