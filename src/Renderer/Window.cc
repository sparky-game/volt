#include <cassert>
#include "Window.hh"

namespace volt::renderer {
  Window::Window(const RenderSystemSpec &spec)
    : m_spec{spec}
  {
    SetTraceLogLevel(LOG_WARNING);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_BORDERLESS_WINDOWED_MODE);
    if (m_spec.is_editor) SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(m_spec.width, m_spec.height, m_spec.name.c_str());
    assert(IsWindowReady());
    if (m_spec.is_editor) {
      m_editorViewport = LoadRenderTexture(m_spec.width, m_spec.height);
      assert(IsRenderTextureReady(*m_editorViewport));
    }
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
    if (m_spec.is_editor) BeginTextureMode(*m_editorViewport);
    DrawTexture(s.data(), x, y, WHITE);
    if (m_spec.is_editor) EndTextureMode();
  }

  void Window::Update(void) {
    EndDrawing();
  }

  const RenderTexture *Window::getEditorViewportFBO(void) const {
    if (m_editorViewport) return &(*m_editorViewport);
    return nullptr;
  }
}
