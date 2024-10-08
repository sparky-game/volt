#include "BehaviourSystem.hh"
#include "../Core/LogSystem.hh"
#include "BehaviourComponent.hh"

namespace volt::runtime {
  BehaviourSystem::BehaviourSystem(void) {
    VOLT_LOG_INFO("BehaviourSystem: created successfully");
  }

  BehaviourSystem::~BehaviourSystem(void) {
    VOLT_LOG_INFO("BehaviourSystem: destroyed successfully");
  }

  void BehaviourSystem::Update(Scene &s) {
    s.ForAll<BehaviourComponent>([](auto e, auto &b) {
      if (b.behaviour) b.behaviour->Update(e);
    });
  }
}
