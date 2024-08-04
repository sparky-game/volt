#pragma once

#include "Window.hh"
#include "EditorLayer.hh"
#include "../Core/Timepoint.hh"

namespace volt::renderer {
  class RenderSystem {
    RenderSystemSpec m_spec;
    Window m_window;
    std::optional<EditorLayer> m_editorLayer;
    int64_t m_minFrameTime;
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
    inline const Window *GetWindowHandle(void) const noexcept { return &m_window; }
    inline bool IsEditor(void) const noexcept { return m_spec.is_editor; }
  };
}
