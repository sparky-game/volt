#include "WindowPTC.hh"
#include "RenderSystem.hh"
#include "RenderComponent.hh"
#include "../Core/LogSystem.hh"

namespace volt::renderer {
  RenderSystem::RenderSystem(const RenderSystemSpec &spec)
    : m_spec{spec}, m_minFrameTime{static_cast<int64_t>(1e9) / m_spec.max_fps}
  {
    using window_type = WindowPTC;
    switch (m_spec.backend) {
    case RenderSystemBackend::Software:
      break;
    case RenderSystemBackend::Raylib:
      assert(false && "RenderSystemBackend::Raylib isn't implemented yet");
      break;
    default:
      assert(false && "A valid RenderSystemBackend needs to be specified");
      break;
    }
    m_window = std::make_unique<window_type>(m_spec.width, m_spec.height, m_spec.name.c_str());
    VOLT_LOG_INFO("volt::renderer::RenderSystem :: created successfully");
  }

  RenderSystem::~RenderSystem(void) {
    VOLT_LOG_INFO("volt::renderer::~RenderSystem :: destroyed successfully");
  }

  void RenderSystem::Update(runtime::Scene &s) {
    m_window->Clear(0);
    s.ForAll<RenderComponent>([this]([[maybe_unused]] auto e, auto &r) {
      m_window->Draw(r.sprite, r.position_x, r.position_y);
    });
    m_window->Update();
  }

  bool RenderSystem::IsRunning(void) const {
    return m_window->IsOpen();
  }

  void RenderSystem::WaitIdle(const core::Timepoint &t) const {
    while ((core::GetTimepoint() - t).count() < m_minFrameTime);
  }
}
