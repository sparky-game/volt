#include <format>
#include <imgui.h>
#include <yaml-cpp/yaml.h>
#include "Rigidbody2DComponent.hh"

namespace volt::runtime {
  Rigidbody2DComponent::Rigidbody2DComponent(void)
    : velocity_x{0}, velocity_y{0}
  {}

  Rigidbody2DComponent::Rigidbody2DComponent(float vel_x, float vel_y)
    : velocity_x{vel_x}, velocity_y{vel_y}
  {}

  void Rigidbody2DComponent::Serialize(YAML::Emitter &out) {
    out << YAML::Key << Rigidbody2DComponent::cmp_name << YAML::BeginMap;
    out << YAML::Key << "Velocity" << YAML::Value << std::format("({:.3f}, {:.3f})", velocity_x, velocity_y);
    out << YAML::EndMap;
  }

  void Rigidbody2DComponent::DrawDetails(void) {
    if (ImGui::CollapsingHeader(Rigidbody2DComponent::cmp_name)) {
      // TODO: use Vector2 to simplify this and be able to pass the data directly.
      float velocity_tmp[] { velocity_x, velocity_y };
      ImGui::InputFloat2("Velocity", velocity_tmp);
      velocity_x = velocity_tmp[0];
      velocity_y = velocity_tmp[1];
    }
  }
}
