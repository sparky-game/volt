#include <imgui.h>
#include <yaml-cpp/yaml.h>
#include "../Core/LogSystem.hh"
#include "Rigidbody2DComponent.hh"

namespace volt::runtime {
  void Rigidbody2DComponent::Serialize(YAML::Emitter &out) {
    out << YAML::Key << Rigidbody2DComponent::cmp_name << YAML::BeginMap;
    std::string type_str;
    switch (type) {
    case Rigidbody2DType::Static:
      type_str = "Static";
      break;
    case Rigidbody2DType::Kinematic:
      type_str = "Kinematic";
      break;
    case Rigidbody2DType::Dynamic:
      type_str = "Dynamic";
      break;
    default:
      assert(0 && "Unreachable");
    }
    out << YAML::Key << "Type" << YAML::Value << type_str;
    out << YAML::Key << "FixedRotation" << YAML::Value << fixedRotation;
    out << YAML::Key << "GravityScale" << YAML::Value << gravityScale;
    out << YAML::EndMap;
  }

  bool Rigidbody2DComponent::Deserialize(YAML::Node &in) {
    static constexpr auto func_name { "volt::runtime::Rigidbody2DComponent::Deserialize" };
    auto type_serialized { in["Type"].as<std::string>() };
    if (type_serialized == "Static") type = Rigidbody2DType::Static;
    else if (type_serialized == "Kinematic") type = Rigidbody2DType::Kinematic;
    else if (type_serialized == "Dynamic") type = Rigidbody2DType::Dynamic;
    else {
      VOLT_LOG_ERROR("{} :: `{}.Type` value not valid", func_name, Rigidbody2DComponent::cmp_name);
      return false;
    }
    try { fixedRotation = in["FixedRotation"].as<bool>(); }
    catch (const YAML::TypedBadConversion<bool> &) {
      VOLT_LOG_ERROR("{} :: `{}.FixedRotation` value format not valid", func_name, Rigidbody2DComponent::cmp_name);
      return false;
    }
    try { gravityScale = in["GravityScale"].as<float>(); }
    catch (const YAML::TypedBadConversion<float> &) {
      VOLT_LOG_ERROR("{} :: `{}.GravityScale` value format not valid", func_name, Rigidbody2DComponent::cmp_name);
      return false;
    }
    return true;
  }

  void Rigidbody2DComponent::Draw(void) {
    if (ImGui::CollapsingHeader(Rigidbody2DComponent::cmp_name)) {
      // TODO: use Vector2 to simplify this and be able to pass the data directly.
      /*
        float velocity_tmp[] { velocity.X(), velocity.Y() };
        ImGui::InputFloat2("Velocity", velocity_tmp);
        velocity.X(velocity_tmp[0]);
        velocity.Y(velocity_tmp[1]);
      */
      // Body Type
      static std::array<const char *, 3> type_opts { "Static", "Kinematic", "Dynamic" };
      static int type_opt_curr {0};
      if (type == Rigidbody2DType::Static) type_opt_curr = 0;
      else if (type == Rigidbody2DType::Kinematic) type_opt_curr = 1;
      else if (type == Rigidbody2DType::Dynamic) type_opt_curr = 2;
      ImGui::Combo("Body Type", &type_opt_curr, type_opts.data(), type_opts.size());
      if (type_opt_curr == 0) type = Rigidbody2DType::Static;
      else if (type_opt_curr == 1) type = Rigidbody2DType::Kinematic;
      else if (type_opt_curr == 2) type = Rigidbody2DType::Dynamic;
      // Freeze Rotation
      ImGui::Checkbox("Freeze Rotation", &fixedRotation);
      // Gravity Scale
      ImGui::InputFloat("Gravity Scale", &gravityScale);
    }
  }
}
