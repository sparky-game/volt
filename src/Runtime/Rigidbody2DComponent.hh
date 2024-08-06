#pragma once

namespace YAML {
  class Emitter;
}

namespace volt::runtime {
  struct Rigidbody2DComponent {
    static inline auto cmp_name { "Rigidbody2D" };
    // Vector2<float> velocity;
    float velocity_x, velocity_y;
    Rigidbody2DComponent(void);
    Rigidbody2DComponent(float vel_x, float vel_y);
    void Serialize(YAML::Emitter &out);
    void DrawDetails(void);
  };
}
