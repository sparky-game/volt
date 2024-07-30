#pragma once

#include "IWindow.hh"
#include "RenderSystemSpec.hh"
#include "../Runtime/Scene.hh"
#include "../Core/Timepoint.hh"

namespace volt::renderer {
  class RenderSystem {
    RenderSystemSpec m_spec;
    int64_t m_minFrameTime;
    std::unique_ptr<IWindow> m_window { nullptr };
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
