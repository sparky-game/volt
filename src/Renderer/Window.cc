#include "Window.hh"

#if defined(__linux__)
#include <tinyPTC/src/linux/tinyptc.h>
#elif defined(_WIN32)
#include <tinyPTC/src/windows/tinyptc.h>
#endif

namespace volt::renderer {
  Window::Window(uint32_t width, uint32_t height, const std::string &name)
    : m_width{width}, m_height{height}, m_name{name}
  {
    ptc_open(m_name.c_str(), m_width, m_height);
    m_data.reserve(m_width * m_height);
    m_data.assign(m_data.capacity(), 0x00000000);
  }

  Window::~Window(void) {
    ptc_close();
  }

  bool Window::IsOpen(void) const {
    return not ptc_process_events();
  }

  void Window::Clear(uint32_t color) {
    std::fill(m_data.begin(), m_data.end(), color);
  }

  void Window::Draw(const Sprite &s, uint32_t x, uint32_t y) {
    for (uint32_t j {0}; j < s.height(); ++j) {
      for (uint32_t i {0}; i < s.width(); ++i) {
        uint32_t screen_x { x + i };
        uint32_t screen_y { y + j };
        if (screen_x < m_width and screen_y < m_height) {
          uint32_t screen_idx { screen_y * m_width + screen_x };
          uint32_t sprite_idx { j * s.width() + i };
          m_data[screen_idx] = s.data()[sprite_idx];
        }
      }
    }
  }

  void Window::Update(void) {
    ptc_update(m_data.data());
  }
}
