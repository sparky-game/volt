#include "PhysicsSystem.hh"
#include "../Core/LogSystem.hh"
#include "TransformComponent.hh"
#include "Rigidbody2DComponent.hh"

extern "C" {
#include <raylib.h>
}

namespace volt::runtime {
  PhysicsSystem::PhysicsSystem(void) {
    VOLT_LOG_INFO("PhysicsSystem: created successfully");
  }

  PhysicsSystem::~PhysicsSystem(void) {
    VOLT_LOG_INFO("PhysicsSystem: destroyed successfully");
  }

  void PhysicsSystem::Update(Scene &s) {
    // Box2D physics simulation update
    b2World_Step(s.GetPhysicsWorld(), 1.0f / 60, 4);
    // Box2D update Transform from Rigidbody2D
    s.ForAll<TransformComponent, Rigidbody2DComponent>([](auto, auto &t, auto &rb) {
      // Position
      b2Vec2 pos = b2Body_GetWorldPoint(rb.GetBodyID(), -rb.GetExtent());
      t.position.X(pos.x);
      t.position.Y(pos.y);
      // Rotation
      t.rotation = b2Rot_GetAngle(b2Body_GetRotation(rb.GetBodyID())) * RAD2DEG;
    });
  }
}
