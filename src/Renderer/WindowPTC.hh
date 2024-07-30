#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include "IWindow.hh"
#include "SpritePTC.hh"

namespace volt::renderer {
  class WindowPTC : public IWindow {
    using data_type = uint32_t;
    uint32_t m_width, m_height;
    std::string m_name;
    std::vector<data_type> m_data;
  public:
    WindowPTC(uint32_t width, uint32_t height, const std::string &name);
    ~WindowPTC(void);
    bool IsOpen(void) const final;
    void Clear(uint32_t color) final;
    void Draw(const ISprite *s, uint32_t x, uint32_t y) final;
    void Update(void) final;
  };
}
