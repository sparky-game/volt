#include "PreRenderSystem.hh"
#include "RenderComponent.hh"
#include "../Runtime/PhysicsComponent.hh"

namespace volt::renderer {
  void PreRenderSystem::Update(runtime::Scene &s) {
    s.ForAll<RenderComponent, runtime::PhysicsComponent>([]([[maybe_unused]] auto e, auto &r, auto &p) {
      r.position_x = std::round(p.position_x);
      r.position_y = std::round(p.position_y);
    });
  }
}
