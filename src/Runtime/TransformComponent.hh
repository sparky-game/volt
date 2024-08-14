#pragma once

#include "../Core/Vector2.hh"

namespace YAML {
  class Emitter;
  class Node;
}

namespace volt::runtime {
  struct TransformComponent {
    static inline auto cmp_name { "Transform" };
    core::Vector2<float> position;
    TransformComponent(void);
    TransformComponent(float pos_x, float pos_y);
    void Serialize(YAML::Emitter &out);
    bool Deserialize(YAML::Node &in);
    void DrawDetails(void);
  };
}
