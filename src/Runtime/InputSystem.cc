#include "InputSystem.hh"
#include "InputComponent.hh"
#include "../Core/LogSystem.hh"
#include "../Core/Timepoint.hh"
#include "Rigidbody2DComponent.hh"

namespace volt::runtime {
  bool GetMouseButtonDown(uint8_t button) {
    return IsMouseButtonDown(button);
  }

  InputSystem::InputSystem(void) {
    VOLT_LOG_INFO("InputSystem: created successfully");
  }

  InputSystem::~InputSystem(void) {
    VOLT_LOG_INFO("InputSystem: destroyed successfully");
  }

  void InputSystem::Update(Scene &s) {
    s.ForAll<InputComponent, Rigidbody2DComponent>([](auto, auto &/*i*/, auto &/*rb*/) {
      /*
        rb.velocity = {0, 0};
        if (IsKeyDown(i.left))  rb.velocity.X((rb.velocity.X() - i.impulse) * core::GetDeltaTime());
        if (IsKeyDown(i.right)) rb.velocity.X((rb.velocity.X() + i.impulse) * core::GetDeltaTime());
        if (IsKeyDown(i.up))    rb.velocity.Y((rb.velocity.Y() - i.impulse) * core::GetDeltaTime());
        if (IsKeyDown(i.down))  rb.velocity.Y((rb.velocity.Y() + i.impulse) * core::GetDeltaTime());
      */
    });
  }
}
