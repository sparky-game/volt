#include "Scene.hh"
#include "BehaviourShootFreq.hh"
#include "TransformComponent.hh"

namespace volt::runtime {
  BehaviourShootFreq::BehaviourShootFreq(uint32_t count)
    : initialCount{count}
  {}

  void BehaviourShootFreq::Update(Entity &e) {
    if (e.HasComponent<TransformComponent>()) {
      [[maybe_unused]] auto &t { e.GetComponent<TransformComponent>() };
      if (counter-- == 0) {
        // Shoot?
        counter = initialCount;
      }
    }
  }
}
