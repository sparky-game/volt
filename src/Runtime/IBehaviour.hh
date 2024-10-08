#pragma once

#include <type_traits>

namespace volt::runtime {
  class Entity;

  struct IBehaviour {
    virtual ~IBehaviour(void) = default;
    virtual void Update(Entity &e) = 0;
  };

  template <typename T>
  concept IBehaviour_t = std::is_base_of<IBehaviour, T>::value;
}
