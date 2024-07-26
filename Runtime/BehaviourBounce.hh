#pragma once

#include "Scene.hh"
#include "IBehaviour.hh"

namespace volt::runtime {
  struct BehaviourBounce : public IBehaviour {
    void Run(Entity &e) final;
  };
}
