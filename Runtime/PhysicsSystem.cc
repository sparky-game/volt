#include "PhysicsSystem.hh"
#include "PhysicsComponent.hh"

namespace volt::runtime {
  void PhysicsSystem::Update(Scene &s) {
    s.ForAll<PhysicsComponent>([]([[maybe_unused]] auto e, auto &p) {
      p.position_x += p.velocity_x;
      p.position_y += p.velocity_y;
    });
  }
}
