#pragma once

#include <memory>
#include "IBehaviour.hh"

namespace volt::runtime {
  struct BehaviourComponent {
    std::unique_ptr<IBehaviour> behaviour { nullptr };
  };
}
