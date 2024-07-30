#pragma once

#include <vector>
#include <cstdint>
#include <filesystem>
#include "ISprite.hh"

namespace volt::renderer {
  class SpritePTC : public ISprite {
    uint32_t m_width, m_height;
    std::vector<uint32_t> m_data;
  public:
    SpritePTC(const std::filesystem::path &path);
    inline uint32_t width(void) const final   { return m_width; }
    inline uint32_t height(void) const final  { return m_height; }
    inline const void *data(void) const final { return reinterpret_cast<const void *>(m_data.data()); }
  };
}
