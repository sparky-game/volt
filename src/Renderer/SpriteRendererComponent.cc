#include <array>
#include <imgui.h>
#include <yaml-cpp/yaml.h>
#include "../Core/LogSystem.hh"
#include "SpriteRendererComponent.hh"

namespace volt::renderer {
  SpriteRendererComponent::SpriteRendererComponent(Sprite &&s) noexcept
    : sprite{std::move(s)}
  {}

  void SpriteRendererComponent::Serialize(YAML::Emitter &out) {
    out << YAML::Key << SpriteRendererComponent::cmp_name << YAML::BeginMap;
    out << YAML::Key << "Sprite" << YAML::Value << (sprite.name().empty() ? "default" : sprite.name());
    out << YAML::EndMap;
  }

  bool SpriteRendererComponent::Deserialize(YAML::Node &in) {
    auto sprite_serialized { in["Sprite"].as<std::string>() };
    try { sprite.Reset(sprite_serialized); }
    catch (const std::runtime_error &) {
      VOLT_LOG_WARN("volt::renderer::SpriteRendererComponent::Deserialize :: Sprite couldn't get resolved, falling back to default");
    }
    return true;
  }

  void SpriteRendererComponent::Draw(void) {
    static bool is_first_time { true };
    static std::array<char, 32> sprite_path { "default" };
    if (is_first_time) {
      size_t len { std::min(sprite.name().size(), sprite_path.size() - 1) };
      std::copy_n(sprite.name().begin(), len, sprite_path.begin());
      sprite_path[len] = 0;
      is_first_time = false;
    }
    if (ImGui::CollapsingHeader(SpriteRendererComponent::cmp_name)) {
      ImGui::InputText("Sprite", sprite_path.data(), sprite_path.size());
      try { sprite.Reset(std::string(sprite_path.data())); }
      catch (const std::runtime_error &) {
        ImGui::TextColored(ImVec4{1, 0.25f, 0.25f, 1}, "Path doesn't resolve to asset");
      }
    }
  }
}
