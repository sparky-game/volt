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
      SetExitKey(0);
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

  void Window::Clear(uint32_t color) const {
    ClearBackground(GetColor(color));
  }

  void Window::Draw(const Sprite &s, const core::Vector2<int32_t> &position) {
    if (m_spec.is_editor) BeginTextureMode(*m_editorViewport);
    DrawTexture(s.data(), position.X(), position.Y(), WHITE);
    if (m_spec.is_editor) EndTextureMode();
  }

  void Window::Update(void) {
    EndDrawing();
  }

  const RenderTexture *Window::GetEditorViewportFBO(void) const {
    if (m_editorViewport) return &(*m_editorViewport);
    return nullptr;
  }
}
