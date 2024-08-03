#pragma once

namespace volt::runtime {
  struct TransformComponent {
    // Vector2<float> position;
    float position_x {0}, position_y {0};
    TransformComponent(void) = default;
    TransformComponent(float pos_x, float pos_y);
    void DrawDetails(void);
  };
}
