#include "PhysicsSystem.hh"
#include "PhysicsComponent.hh"
#include "../Core/LogSystem.hh"

namespace volt::runtime {
  PhysicsSystem::PhysicsSystem(void) {
    VOLT_LOG_INFO("volt::runtime::PhysicsSystem :: created successfully");
  }

  PhysicsSystem::~PhysicsSystem(void) {
    VOLT_LOG_INFO("volt::runtime::~PhysicsSystem :: destroyed successfully");
  }

  void PhysicsSystem::Update(Scene &s) {
    s.ForAll<PhysicsComponent>([]([[maybe_unused]] auto e, auto &p) {
      p.position_x += p.velocity_x;
      p.position_y += p.velocity_y;
    });
  }
}
