#pragma once

namespace volt::runtime {
  struct Rigidbody2DComponent {
    // Vector2<float> velocity;
    float velocity_x, velocity_y;
    Rigidbody2DComponent(float vel_x, float vel_y)
      : velocity_x{vel_x}, velocity_y{vel_y}
    {}
  };
}
