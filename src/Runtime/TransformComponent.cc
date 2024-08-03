#include <imgui.h>
#include "TransformComponent.hh"

namespace volt::runtime {
  TransformComponent::TransformComponent(float pos_x, float pos_y)
    : position_x{pos_x}, position_y{pos_y}
  {}

  void TransformComponent::DrawDetails(void) {
    if (ImGui::CollapsingHeader("Transform")) {
      // TODO: use Vector2 to simplify this and be able to pass the data directly.
      float position_tmp[] { position_x, position_y };
      ImGui::InputFloat2("Position", position_tmp);
      position_x = position_tmp[0];
      position_y = position_tmp[1];
    }
  }
}
