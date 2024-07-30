#include "InputSystem.hh"
#include "InputComponent.hh"
#include "PhysicsComponent.hh"
#include "../Core/LogSystem.hh"

namespace volt::runtime {
  InputSystem::InputSystem(void) {
    VOLT_LOG_INFO("volt::runtime::InputSystem :: created successfully");
  }

  InputSystem::~InputSystem(void) {
    VOLT_LOG_INFO("volt::runtime::~InputSystem :: destroyed successfully");
  }

  void InputSystem::Update(Scene &s) {
    s.ForAll<InputComponent, PhysicsComponent>([]([[maybe_unused]] auto e, auto &i, auto &p) {
      p.velocity_x = 0;
      p.velocity_y = 0;
      if (IsKeyDown(i.left))  p.velocity_x -= i.impulse;
      if (IsKeyDown(i.right)) p.velocity_x += i.impulse;
      if (IsKeyDown(i.up))    p.velocity_y -= i.impulse;
      if (IsKeyDown(i.down))  p.velocity_y += i.impulse;
    });
  }
}
