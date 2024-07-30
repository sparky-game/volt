#include "InputSystem.hh"
#include "InputComponent.hh"
#include "PhysicsComponent.hh"
#include "../Core/LogSystem.hh"

#if defined(__linux__)
#include <tinyPTC/src/linux/tinyptc.h>
#elif defined(_WIN32)
#include <tinyPTC/src/windows/tinyptc.h>
#endif

namespace volt::runtime {
  InputSystem::InputSystem(void) {
    ptc_set_on_keypress(onKeyPress);
    ptc_set_on_keyrelease(onKeyRelease);
    VOLT_LOG_INFO("volt::runtime::InputSystem :: created successfully");
  }

  InputSystem::~InputSystem(void) {
    VOLT_LOG_INFO("volt::runtime::~InputSystem :: destroyed successfully");
  }

  void InputSystem::Update(Scene &s) {
    s.ForAll<InputComponent, PhysicsComponent>([]([[maybe_unused]] auto e, auto &i, auto &p) {
      p.velocity_x = 0;
      p.velocity_y = 0;
      if (s_keyboard.IsKeyPressed(i.left))  p.velocity_x -= i.impulse;
      if (s_keyboard.IsKeyPressed(i.right)) p.velocity_x += i.impulse;
      if (s_keyboard.IsKeyPressed(i.up))    p.velocity_y -= i.impulse;
      if (s_keyboard.IsKeyPressed(i.down))  p.velocity_y += i.impulse;
    });
  }
}
