#include "PreRenderSystem.hh"
#include "../Core/LogSystem.hh"
#include "SpriteRendererComponent.hh"
#include "../Runtime/TransformComponent.hh"

namespace volt::renderer {
  PreRenderSystem::PreRenderSystem(const RenderSystem &renderer) : m_renderer{renderer} {
    VOLT_LOG_INFO("volt::renderer::PreRenderSystem :: created successfully");
  }

  PreRenderSystem::~PreRenderSystem(void) {
    VOLT_LOG_INFO("volt::renderer::~PreRenderSystem :: destroyed successfully");
  }

  void PreRenderSystem::Update(runtime::Scene &s) {
    s.ForAll<SpriteRendererComponent, runtime::TransformComponent>([](auto, auto &r, auto &t) {
      r.position.X(std::round(t.position.X()));
      r.position.Y(std::round(t.position.Y()));
      r.rotation = t.rotation;
      r.scale = t.scale;
    });
    BeginDrawing();
    m_renderer.GetWindowHandle()->Clear(0);
  }
}
