#include "Scene.hh"
#include "PhysicsComponent.hh"
#include "BehaviourShootFreq.hh"

namespace volt::runtime {
  BehaviourShootFreq::BehaviourShootFreq(uint32_t count)
    : initialCount{count}
  {}

  void BehaviourShootFreq::Run(Entity &e) {
    if (e.HasComponent<PhysicsComponent>()) {
      [[maybe_unused]] auto &p { e.GetComponent<PhysicsComponent>() };
      if (counter-- == 0) {
        // Shoot?
        counter = initialCount;
      }
    }
  }
}
