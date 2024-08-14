#pragma once

#include "../Core/Vector2.hh"

namespace YAML {
  class Emitter;
  class Node;
}

namespace volt::runtime {
  struct Rigidbody2DComponent {
    static inline auto cmp_name { "Rigidbody2D" };
    core::Vector2<float> velocity;
    Rigidbody2DComponent(void);
    Rigidbody2DComponent(float vel_x, float vel_y);
    void Serialize(YAML::Emitter &out);
    bool Deserialize(YAML::Node &in);
    void DrawDetails(void);
  };
}
