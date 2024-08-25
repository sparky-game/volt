#pragma once

namespace volt::runtime {
  class Entity;

  struct IBehaviour {
    virtual ~IBehaviour(void) = default;
    virtual void Update(Entity &e) = 0;
  };
}
