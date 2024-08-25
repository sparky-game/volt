#pragma once

#include "Scene.hh"
#include "IBehaviour.hh"

namespace volt::runtime {
  struct BehaviourBounce : public IBehaviour {
    void Update(Entity &e) final;
  };
}
