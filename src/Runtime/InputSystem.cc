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
    s.ForAll<InputComponent, Rigidbody2DComponent>([]([[maybe_unused]] auto e, auto &i, auto &rb) {
      rb.velocity_x = 0;
      rb.velocity_y = 0;
      if (IsKeyDown(i.left))  rb.velocity_x -= i.impulse;
      if (IsKeyDown(i.right)) rb.velocity_x += i.impulse;
      if (IsKeyDown(i.up))    rb.velocity_y -= i.impulse;
      if (IsKeyDown(i.down))  rb.velocity_y += i.impulse;
    });
  }
}
