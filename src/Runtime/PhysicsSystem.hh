#pragma once

#include "Scene.hh"

namespace volt::runtime {
  struct PhysicsSystem {
    PhysicsSystem(void);
    PhysicsSystem(const PhysicsSystem &) = delete;
    PhysicsSystem(PhysicsSystem &&) = delete;
    PhysicsSystem &operator=(const PhysicsSystem &) = delete;
    PhysicsSystem &operator=(PhysicsSystem &&) = delete;
    ~PhysicsSystem(void);
    void Update(Scene &s);
  };
}
