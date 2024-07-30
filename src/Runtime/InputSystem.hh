#pragma once

#include "Scene.hh"

namespace volt::runtime {
  struct InputSystem {
    InputSystem(void);
    InputSystem(const InputSystem &) = delete;
    InputSystem(InputSystem &&) = delete;
    InputSystem &operator=(const InputSystem &) = delete;
    InputSystem &operator=(InputSystem &&) = delete;
    ~InputSystem(void);
    void Update(Scene &s);
  };
}
