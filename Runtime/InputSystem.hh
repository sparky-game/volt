#pragma once

#include "Scene.hh"
#include "Keyboard.hh"

namespace volt::runtime {
  class InputSystem {
    static inline Keyboard s_keyboard;
    static inline void onKeyPress(core::KeyValueType k)   { s_keyboard.OnKeyPressed(Value2Key(k));  }
    static inline void onKeyRelease(core::KeyValueType k) { s_keyboard.OnKeyReleased(Value2Key(k)); }
  public:
    InputSystem(void);
    void Update(Scene &s);
  };
}
