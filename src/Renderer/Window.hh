#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <optional>
#include "Sprite.hh"
#include "RenderSystemSpec.hh"

namespace volt::renderer {
  class Window {
    RenderSystemSpec m_spec;
    std::optional<RenderTexture> m_editorViewport;
  public:
    Window(const RenderSystemSpec &spec);
    ~Window(void);
    bool IsOpen(void) const;
    void Clear(uint32_t color);
    void Draw(const Sprite &s, uint32_t x, uint32_t y);
    void Update(void);
    const RenderTexture *getEditorViewportFBO(void) const;
  };
}
