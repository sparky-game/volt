#pragma once

#include "Scene.hh"

namespace volt::runtime {
  struct PhysicsSystem {
    void Update(Scene &s);
  };
}
