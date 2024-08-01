#pragma once

#include "RenderSystem.hh"
#include "../Runtime/Scene.hh"

namespace volt::renderer {
  class PreRenderSystem {
    const RenderSystem &m_renderer;
  public:
    PreRenderSystem(const RenderSystem &renderer);
    PreRenderSystem(const PreRenderSystem &) = delete;
    PreRenderSystem(PreRenderSystem &&) = delete;
    PreRenderSystem &operator=(const PreRenderSystem &) = delete;
    PreRenderSystem &operator=(PreRenderSystem &&) = delete;
    ~PreRenderSystem(void);
    void Update(runtime::Scene &s);
  };
}
