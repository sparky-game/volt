#pragma once

namespace volt::runtime {
  struct PhysicsComponent {
    // Vector2<float> position;
    float position_x, position_y;
    // Vector2<float> velocity;
    float velocity_x, velocity_y;
    PhysicsComponent(float pos_x, float pos_y, float vel_x, float vel_y)
      : position_x{pos_x}, position_y{pos_y}, velocity_x{vel_x}, velocity_y{vel_y}
    {}
  };
}
