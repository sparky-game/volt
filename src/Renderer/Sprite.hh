#pragma once

#include <vector>
#include <cstdint>
#include <filesystem>

extern "C" {
#include <raylib.h>
}

namespace volt::renderer {
  class Sprite {
    uint32_t m_width, m_height;
    Texture m_data;
  public:
    Sprite(const std::filesystem::path &path);
    Sprite(Sprite &&s) noexcept;
    Sprite(const Sprite &) = delete;
    Sprite &operator=(const Sprite &) = delete;
    ~Sprite(void);
    inline uint32_t width(void) const  { return m_width;  }
    inline uint32_t height(void) const { return m_height; }
    inline Texture2D data(void) const  { return m_data;   }
  };
}
