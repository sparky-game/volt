#pragma once

#include "Keyboard.hh"

namespace volt::runtime {
  struct InputComponent {
    core::Key up    { core::Key::W };
    core::Key left  { core::Key::A };
    core::Key down  { core::Key::S };
    core::Key right { core::Key::D };
    float impulse   { 4.0f };
  };
}
