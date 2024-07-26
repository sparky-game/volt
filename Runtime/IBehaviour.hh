#pragma once

namespace volt::runtime {
  class Entity;

  struct IBehaviour {
    virtual ~IBehaviour(void) = default;
    virtual void Run(Entity &e) = 0;
  };
}
