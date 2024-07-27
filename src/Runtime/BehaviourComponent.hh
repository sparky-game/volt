#pragma once

#include "IBehaviour.hh"

namespace volt::runtime {
  struct BehaviourComponent {
    std::unique_ptr<IBehaviour> behaviour { nullptr };
  };
}
