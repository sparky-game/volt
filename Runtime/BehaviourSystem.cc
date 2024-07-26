#include "BehaviourSystem.hh"
#include "BehaviourComponent.hh"

namespace volt::runtime {
  void BehaviourSystem::Update(Scene &s) {
    s.ForAll<BehaviourComponent>([](auto e, auto &b) {
      if (b.behaviour) b.behaviour->Run(e);
    });
  }
}
