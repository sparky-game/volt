#include "Window.hh"
#include "RenderSystem.hh"
#include "RenderComponent.hh"
#include "../Core/LogSystem.hh"

namespace volt::renderer {
  RenderSystem::RenderSystem(const RenderSystemSpec &spec)
    : m_spec{spec}, m_window{m_spec.width, m_spec.height, m_spec.name.c_str()}, m_minFrameTime{static_cast<int64_t>(1e9) / m_spec.max_fps}
  {
    VOLT_LOG_INFO("volt::renderer::RenderSystem :: created successfully");
  }

  RenderSystem::~RenderSystem(void) {
    VOLT_LOG_INFO("volt::renderer::~RenderSystem :: destroyed successfully");
  }

  void RenderSystem::Update(runtime::Scene &s) {
    m_window.Clear(0);
    s.ForAll<RenderComponent>([this]([[maybe_unused]] auto e, auto &r) {
      m_window.Draw(r.sprite, r.position_x, r.position_y);
    });
    m_window.Update();
  }

  bool RenderSystem::IsRunning(void) const {
    return m_window.IsOpen();
  }

  void RenderSystem::WaitIdle(const core::Timepoint &t) const {
    while ((core::GetTimepoint() - t).count() < m_minFrameTime);
  }
}
