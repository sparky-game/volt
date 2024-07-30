#pragma once

#include "Scene.hh"

namespace volt::runtime {
  struct BehaviourSystem {
    BehaviourSystem(void);
    BehaviourSystem(const BehaviourSystem &) = delete;
    BehaviourSystem(BehaviourSystem &&) = delete;
    BehaviourSystem &operator=(const BehaviourSystem &) = delete;
    BehaviourSystem &operator=(BehaviourSystem &&) = delete;
    ~BehaviourSystem(void);
    void Update(Scene &s);
  };
}
