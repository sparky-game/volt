#include <cassert>
#include "Window.hh"

namespace volt::renderer {
  Window::Window(uint32_t width, uint32_t height, const std::string &name)
    : m_width{width}, m_height{height}, m_name{name}
  {
    SetTraceLogLevel(LOG_WARNING);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_BORDERLESS_WINDOWED_MODE);
    InitWindow(m_width, m_height, m_name.c_str());
    assert(IsWindowReady());
  }

  Window::~Window(void) {
    CloseWindow();
  }

  bool Window::IsOpen(void) const {
    return not WindowShouldClose();
  }

  void Window::Clear(uint32_t color) {
    ClearBackground(GetColor(color));
  }

  void Window::Draw(const Sprite &s, uint32_t x, uint32_t y) {
    DrawTexture(s.data(), x, y, WHITE);
  }

  void Window::Update(void) {
    EndDrawing();
  }
}
