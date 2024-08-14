#include "BehaviourBounce.hh"
#include "TransformComponent.hh"
#include "Rigidbody2DComponent.hh"

namespace volt::runtime {
  void BehaviourBounce::Run(Entity &e) {
    if (e.HasComponent<TransformComponent>() && e.HasComponent<Rigidbody2DComponent>()) {
      auto &t  { e.GetComponent<TransformComponent>()   };
      auto &rb { e.GetComponent<Rigidbody2DComponent>() };
      if (t.position.X() <= 0)   { t.position.X(0); rb.velocity.X(-rb.velocity.X());   }
      if (t.position.Y() <= 0)   { t.position.Y(0); rb.velocity.Y(-rb.velocity.Y());   }
      if (t.position.X() >= 640) { t.position.X(640); rb.velocity.X(-rb.velocity.X()); }
      if (t.position.Y() >= 456) { t.position.Y(456); rb.velocity.Y(-rb.velocity.Y()); }
    }
  }
}
