#pragma once

#include "Scene.hh"

namespace volt::runtime {
  struct BehaviourSystem {
    void Update(Scene &s);
  };
}
