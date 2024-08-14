#include "InputSystem.hh"
#include "InputComponent.hh"
#include "../Core/LogSystem.hh"
#include "Rigidbody2DComponent.hh"

namespace volt::runtime {
  InputSystem::InputSystem(void) {
    VOLT_LOG_INFO("volt::runtime::InputSystem :: created successfully");
  }

  InputSystem::~InputSystem(void) {
    VOLT_LOG_INFO("volt::runtime::~InputSystem :: destroyed successfully");
  }

  void InputSystem::Update(Scene &s) {
    s.ForAll<InputComponent, Rigidbody2DComponent>([](auto, auto &i, auto &rb) {
      rb.velocity = {0, 0};
      if (IsKeyDown(i.left))  rb.velocity.X(rb.velocity.X() - i.impulse);
      if (IsKeyDown(i.right)) rb.velocity.X(rb.velocity.X() + i.impulse);
      if (IsKeyDown(i.up))    rb.velocity.Y(rb.velocity.Y() - i.impulse);
      if (IsKeyDown(i.down))  rb.velocity.Y(rb.velocity.Y() + i.impulse);
    });
  }
}
