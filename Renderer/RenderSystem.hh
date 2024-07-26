#pragma once

#include "Window.hh"
#include "../Runtime/Scene.hh"
#include "../Core/Timepoint.hh"

namespace volt::renderer {
  struct RenderSystemSpec {
    uint32_t width, height;
    std::string name;
    uint32_t max_fps;
  };

  class RenderSystem {
    RenderSystemSpec m_spec;
    Window m_window;
    int64_t m_minFrameTime;
  public:
    RenderSystem(const RenderSystemSpec &spec);
    RenderSystem(const RenderSystem &) = delete;
    RenderSystem(RenderSystem &&) = delete;
    RenderSystem &operator=(const RenderSystem &) = delete;
    RenderSystem &operator=(RenderSystem &&) = delete;
    void Update(runtime::Scene &s);
    bool IsRunning(void) const;
    void WaitIdle(const core::Timepoint &t) const;
  };
}
