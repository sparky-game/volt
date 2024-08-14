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
    s.ForAll<TransformComponent, Rigidbody2DComponent>([](auto, auto &t, auto &rb) {
      t.position.X(t.position.X() + rb.velocity.X());
      t.position.Y(t.position.Y() + rb.velocity.Y());
    });
  }
}
