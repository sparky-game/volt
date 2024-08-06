#pragma once

namespace YAML {
  class Emitter;
}

namespace volt::runtime {
  struct TransformComponent {
    static inline auto cmp_name { "Transform" };
    // Vector2<float> position;
    float position_x, position_y;
    TransformComponent(void);
    TransformComponent(float pos_x, float pos_y);
    void Serialize(YAML::Emitter &out);
    void DrawDetails(void);
  };
}
