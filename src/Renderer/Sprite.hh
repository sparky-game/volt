#pragma once

#include <vector>
#include <cstdint>
#include <filesystem>

namespace volt::renderer {
  class Sprite {
    uint32_t m_width, m_height;
    std::vector<uint32_t> m_data;
  public:
    Sprite(const std::filesystem::path &path);
    inline uint32_t width(void) const { return m_width; }
    inline uint32_t height(void) const { return m_height; }
    inline auto data(void) const { return m_data.data(); }
  };
}
