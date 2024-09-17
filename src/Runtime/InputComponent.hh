#pragma once

#include <cstdint>

extern "C" {
#include <raylib.h>
}

namespace volt::runtime {
  struct InputComponent {
    uint16_t up    { KEY_W };
    uint16_t left  { KEY_A };
    uint16_t down  { KEY_S };
    uint16_t right { KEY_D };
    float impulse  { 250   };
  };
}
