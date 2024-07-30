#pragma once

#include <string>
#include <cstdint>

namespace volt::renderer {
  enum class RenderSystemBackend {
    Null,
    Software,
    Raylib
  };

  struct RenderSystemSpec {
    RenderSystemBackend backend;
    uint32_t width, height;
    std::string name;
    uint32_t max_fps;
  };
}
