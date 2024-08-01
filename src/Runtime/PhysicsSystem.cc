#include "PhysicsSystem.hh"
#include "../Core/LogSystem.hh"
#include "TransformComponent.hh"
#include "Rigidbody2DComponent.hh"

namespace volt::runtime {
  PhysicsSystem::PhysicsSystem(void) {
    VOLT_LOG_INFO("volt::runtime::PhysicsSystem :: created successfully");
  }

  PhysicsSystem::~PhysicsSystem(void) {
    VOLT_LOG_INFO("volt::runtime::~PhysicsSystem :: destroyed successfully");
  }

  void PhysicsSystem::Update(Scene &s) {
    s.ForAll<TransformComponent, Rigidbody2DComponent>([]([[maybe_unused]] auto e, auto &t, auto &rb) {
      t.position_x += rb.velocity_x;
      t.position_y += rb.velocity_y;
    });
  }
}
