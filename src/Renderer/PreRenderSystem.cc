#include "PreRenderSystem.hh"
#include "RenderComponent.hh"
#include "../Core/LogSystem.hh"
#include "../Runtime/TransformComponent.hh"

namespace volt::renderer {
  PreRenderSystem::PreRenderSystem(const RenderSystem &renderer) : m_renderer{renderer} {
    VOLT_LOG_INFO("volt::renderer::PreRenderSystem :: created successfully");
  }

  PreRenderSystem::~PreRenderSystem(void) {
    VOLT_LOG_INFO("volt::renderer::~PreRenderSystem :: destroyed successfully");
  }

  void PreRenderSystem::Update(runtime::Scene &s) {
    s.ForAll<RenderComponent, runtime::TransformComponent>([]([[maybe_unused]] auto e, auto &r, auto &t) {
      r.position_x = std::round(t.position_x);
      r.position_y = std::round(t.position_y);
    });
    BeginDrawing();
    m_renderer.GetWindowHandle()->Clear(0);
  }
}
