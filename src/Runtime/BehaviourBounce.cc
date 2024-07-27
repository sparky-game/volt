#include "BehaviourBounce.hh"
#include "PhysicsComponent.hh"

namespace volt::runtime {
  void BehaviourBounce::Run(Entity &e) {
    if (e.HasComponent<PhysicsComponent>()) {
      auto &p { e.GetComponent<PhysicsComponent>() };
      if (p.position_x <= 0)   { p.position_x = 0; p.velocity_x = -p.velocity_x;   }
      if (p.position_y <= 0)   { p.position_y = 0; p.velocity_y = -p.velocity_y;   }
      if (p.position_x >= 640) { p.position_x = 640; p.velocity_x = -p.velocity_x; }
      if (p.position_y >= 456) { p.position_y = 456; p.velocity_y = -p.velocity_y; }
    }
  }
}
