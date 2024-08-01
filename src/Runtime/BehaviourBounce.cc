#include "BehaviourBounce.hh"
#include "TransformComponent.hh"
#include "Rigidbody2DComponent.hh"

namespace volt::runtime {
  void BehaviourBounce::Run(Entity &e) {
    if (e.HasComponent<TransformComponent>() && e.HasComponent<Rigidbody2DComponent>()) {
      auto &t  { e.GetComponent<TransformComponent>()   };
      auto &rb { e.GetComponent<Rigidbody2DComponent>() };
      if (t.position_x <= 0)   { t.position_x = 0; rb.velocity_x = -rb.velocity_x;   }
      if (t.position_y <= 0)   { t.position_y = 0; rb.velocity_y = -rb.velocity_y;   }
      if (t.position_x >= 640) { t.position_x = 640; rb.velocity_x = -rb.velocity_x; }
      if (t.position_y >= 456) { t.position_y = 456; rb.velocity_y = -rb.velocity_y; }
    }
  }
}
