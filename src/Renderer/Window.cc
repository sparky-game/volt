#include <cassert>
#include "Window.hh"
#include "SpriteRendererComponent.hh"

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

  void Window::Draw(const SpriteRendererComponent &sr) {
    if (m_spec.is_editor) BeginTextureMode(*m_editorViewport);
    float tex_width = sr.sprite.data().width, tex_height = sr.sprite.data().height;
    float pos_x = sr.position.X() + (tex_width / 2), pos_y = sr.position.Y() + (tex_height / 2);
    DrawTexturePro(sr.sprite.data(),
                   {0, 0, tex_width, tex_height},
                   {pos_x, pos_y, tex_width * sr.scale, tex_height * sr.scale},
                   {(tex_width / 2) * sr.scale, (tex_height / 2) * sr.scale},
                   sr.rotation,
                   GetColor(sr.color));
    if (m_spec.is_editor) {
      // TODO: this circle is provisional, replace it with a gizmo to move, rotate and scale it.
      DrawCircle(pos_x, pos_y, 4, RED);
      EndTextureMode();
    }
  }

  void Window::Update(void) {
    EndDrawing();
  }

  const RenderTexture *Window::GetEditorViewportFBO(void) const {
    if (m_editorViewport) return &(*m_editorViewport);
    return nullptr;
  }
}
