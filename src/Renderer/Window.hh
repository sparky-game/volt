#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include "Sprite.hh"

namespace volt::renderer {
  class Window {
    uint32_t m_width, m_height;
    std::string m_name;
    std::vector<uint32_t> m_data;
  public:
    Window(uint32_t width, uint32_t height, const std::string &name);
    ~Window(void);
    bool IsOpen(void) const;
    void Clear(uint32_t color);
    void Draw(const Sprite &s, uint32_t x, uint32_t y);
    void Update(void);
  };
}
