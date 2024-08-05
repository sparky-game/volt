#pragma once

#include "../Runtime/Scene.hh"
#include "../Core/SnowflakeID.hh"

namespace volt::renderer {
  class EditorLayer {
    bool m_closeRequested { false };
    core::SnowflakeID::value_type m_selectedEntityID {0};
    void drawMenubar(void) noexcept;
    void drawControls(runtime::Scene &s) noexcept;
    void drawScene(Window &w) const noexcept;
    void drawHierarchy(runtime::Scene &s) noexcept;
    void drawInspector(runtime::Scene &s) const noexcept;
    void drawProject(void) const noexcept;
    void drawStats(void) const noexcept;
  public:
    void Setup(void) const noexcept;
    void Draw(runtime::Scene &s, Window &w) noexcept;
    inline bool IsCloseRequested(void) const noexcept { return m_closeRequested; }
  };
}
