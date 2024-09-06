#include <imgui.h>
#include <yaml-cpp/yaml.h>
#include "../Core/LogSystem.hh"
#include "TransformComponent.hh"

namespace volt::runtime {
  TransformComponent::TransformComponent(const core::Vector2<float> &p, float r, float s)
    : position{p}, rotation{r}, scale{s}
  {}

  void TransformComponent::Serialize(YAML::Emitter &out) {
    out << YAML::Key << TransformComponent::cmp_name << YAML::BeginMap;
    out << YAML::Key << "Position" << YAML::Value << position.ToString();
    out << YAML::Key << "Rotation" << YAML::Value << fmt::format("{:.3f}", rotation);
    out << YAML::Key << "Scale" << YAML::Value << fmt::format("{:.3f}", scale);
    out << YAML::EndMap;
  }

  bool TransformComponent::Deserialize(YAML::Node &in) {
    static constexpr auto func_name { "volt::runtime::TransformComponent::Deserialize" };
    auto position_serialized { in["Position"].as<std::string>() };
    auto rotation_serialized { in["Rotation"].as<std::string>() };
    auto scale_serialized    { in["Scale"].as<std::string>()    };
    float position_tmp_x {0}, position_tmp_y {0};
    float rotation_tmp {0};
    float scale_tmp {0};
    if (2 != std::sscanf(position_serialized.c_str(), "(%f, %f)", &position_tmp_x, &position_tmp_y)) {
      VOLT_LOG_ERROR("{} :: `{}.Position` value format not valid",
                     func_name, TransformComponent::cmp_name);
      return false;
    }
    if (1 != std::sscanf(rotation_serialized.c_str(), "%f", &rotation_tmp)) {
      VOLT_LOG_ERROR("{} :: `{}.Rotation` value format not valid",
                     func_name, TransformComponent::cmp_name);
      return false;
    }
    if (1 != std::sscanf(scale_serialized.c_str(), "%f", &scale_tmp)) {
      VOLT_LOG_ERROR("{} :: `{}.Scale` value format not valid",
                     func_name, TransformComponent::cmp_name);
      return false;
    }
    position.X(position_tmp_x);
    position.Y(position_tmp_y);
    rotation = rotation_tmp;
    scale = scale_tmp;
    return true;
  }

  void TransformComponent::Draw(void) {
    if (ImGui::CollapsingHeader(TransformComponent::cmp_name)) {
      // TODO: use Vector2 to simplify this and be able to pass the data directly.
      float position_tmp[] { position.X(), position.Y() };
      ImGui::InputFloat2("Position", position_tmp);
      ImGui::InputFloat("Rotation", &rotation);
      ImGui::InputFloat("Scale", &scale);
      position.X(position_tmp[0]);
      position.Y(position_tmp[1]);
    }
  }
}
