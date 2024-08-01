#pragma once

#include "Window.hh"
#include "../Runtime/Scene.hh"
#include "../Core/Timepoint.hh"

namespace volt::renderer {
  class RenderSystem {
    RenderSystemSpec m_spec;
    Window m_window;
    int64_t m_minFrameTime;
    bool m_closeRequested;
    void editorLayerSetup(void) const;
    void editorLayerDraw(void);
  public:
    RenderSystem(const RenderSystemSpec &spec);
    RenderSystem(const RenderSystem &) = delete;
    RenderSystem(RenderSystem &&) = delete;
    RenderSystem &operator=(const RenderSystem &) = delete;
    RenderSystem &operator=(RenderSystem &&) = delete;
    ~RenderSystem(void);
    void Update(runtime::Scene &s);
    bool IsRunning(void) const;
    void WaitIdle(const core::Timepoint &t) const;
  };
}
