#include "Window.hh"
#include "RenderSystem.hh"
#include "../Core/LogSystem.hh"
#include "SpriteRendererComponent.hh"

namespace volt::renderer {
  RenderSystem::RenderSystem(const RenderSystemSpec &spec)
    : m_spec{spec}, m_window{m_spec}, m_minFrameTime{static_cast<int64_t>(1e9) / m_spec.max_fps}
  {
    if (IsEditor()) {
      m_editorLayer = std::make_optional<EditorLayer>();
      m_editorLayer->Setup();
    }
    VOLT_LOG_INFO("volt::renderer::RenderSystem :: created successfully");
  }

  RenderSystem::~RenderSystem(void) {
    VOLT_LOG_INFO("volt::renderer::~RenderSystem :: destroyed successfully");
  }

  void RenderSystem::Update(runtime::Scene &s) {
    if (IsEditor()) {
      BeginTextureMode(*m_window.GetEditorViewportFBO());
      // NOTE: to visually distinguish actual scene viewport
      ClearBackground(GetColor(0x333333FF));
    }
    s.ForAll<SpriteRendererComponent>([this](auto, auto &r) {
      m_window.Draw(r.sprite, r.position);
    });
    if (IsEditor()) {
      EndTextureMode();
      m_editorLayer->Draw(s, m_window);
    }
    m_window.Update();
  }

  bool RenderSystem::IsRunning(void) const {
    if (IsEditor() and m_editorLayer->IsCloseRequested()) return false;
    return m_window.IsOpen();
  }

  void RenderSystem::WaitIdle(const core::Timepoint &t) const {
    while ((core::GetTimepoint() - t).count() < m_minFrameTime);
  }
}
