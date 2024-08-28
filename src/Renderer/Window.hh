#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <optional>
#include "Sprite.hh"
#include "../Core/Vector2.hh"
#include "RenderSystemSpec.hh"

namespace volt::renderer {
  struct SpriteRendererComponent;

  class Window {
    RenderSystemSpec m_spec;
    std::optional<RenderTexture> m_editorViewport;
  public:
    Window(const RenderSystemSpec &spec);
    ~Window(void);
    bool IsOpen(void) const;
    void Clear(uint32_t color) const;
    void Draw(const SpriteRendererComponent &sr);
    void Update(void);
    const RenderTexture *GetEditorViewportFBO(void) const;
  };
}
