#pragma once

#include <type_traits>

namespace YAML {
  class Emitter;
  class Node;
}

namespace volt::runtime {
  struct IComponent {
    virtual ~IComponent(void) = default;
    virtual void Serialize(YAML::Emitter &out) = 0;
    virtual bool Deserialize(YAML::Node &in) = 0;
    virtual void Draw(void) = 0;
  };

  template <typename T>
  concept IComponent_t = std::is_base_of<IComponent, T>::value;
}
