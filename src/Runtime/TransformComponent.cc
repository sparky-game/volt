#include <format>
#include <imgui.h>
#include <yaml-cpp/yaml.h>
#include "../Core/LogSystem.hh"
#include "TransformComponent.hh"

namespace volt::runtime {
  TransformComponent::TransformComponent(void)
    : position_x{0}, position_y{0}
  {}

  TransformComponent::TransformComponent(float pos_x, float pos_y)
    : position_x{pos_x}, position_y{pos_y}
  {}

  void TransformComponent::Serialize(YAML::Emitter &out) {
    out << YAML::Key << TransformComponent::cmp_name << YAML::BeginMap;
    out << YAML::Key << "Position" << YAML::Value << std::format("({:.3f}, {:.3f})", position_x, position_y);
    out << YAML::EndMap;
  }

  bool TransformComponent::Deserialize(YAML::Node &in) {
    auto position_serialized { in["Position"].as<std::string>() };
    float position_tmp_x {0}, position_tmp_y {0};
    if (2 != std::sscanf(position_serialized.c_str(), "(%f, %f)", &position_tmp_x, &position_tmp_y)) {
      VOLT_LOG_ERROR("volt::runtime::TransformComponent::Deserialize :: `{}.Position` value format not valid",
                     TransformComponent::cmp_name);
      return false;
    }
    position_x = position_tmp_x;
    position_y = position_tmp_y;
    return true;
  }

  void TransformComponent::DrawDetails(void) {
    if (ImGui::CollapsingHeader(TransformComponent::cmp_name)) {
      // TODO: use Vector2 to simplify this and be able to pass the data directly.
      float position_tmp[] { position_x, position_y };
      ImGui::InputFloat2("Position", position_tmp);
      position_x = position_tmp[0];
      position_y = position_tmp[1];
    }
  }
}
