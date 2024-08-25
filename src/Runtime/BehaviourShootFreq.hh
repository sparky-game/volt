#pragma once

#include <cstdint>
#include "IBehaviour.hh"

namespace volt::runtime {
  struct BehaviourShootFreq : public IBehaviour {
    BehaviourShootFreq(uint32_t count);
    uint32_t initialCount;
    uint32_t counter { initialCount };
    void Update(Entity &e) final;
  };
}
