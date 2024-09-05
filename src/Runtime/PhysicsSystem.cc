#include "PhysicsSystem.hh"
#include "../Core/LogSystem.hh"
#include "TransformComponent.hh"
#include "Rigidbody2DComponent.hh"

namespace volt::runtime {
  PhysicsSystem::PhysicsSystem(void) {
    VOLT_LOG_INFO("PhysicsSystem: created successfully");
  }

  PhysicsSystem::~PhysicsSystem(void) {
    VOLT_LOG_INFO("PhysicsSystem: destroyed successfully");
  }

  void PhysicsSystem::Update(Scene &s) {
    s.ForAll<TransformComponent, Rigidbody2DComponent>([](auto, auto &t, auto &rb) {
      t.position += rb.velocity;
    });
  }
}
