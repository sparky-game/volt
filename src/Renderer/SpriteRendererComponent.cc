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
    out << YAML::Key << "Color" << YAML::Value << fmt::format("{:#x}", color);
    out << YAML::EndMap;
  }

  bool SpriteRendererComponent::Deserialize(YAML::Node &in) {
    static constexpr auto func_name { "volt::renderer::SpriteRendererComponent::Deserialize" };
    auto sprite_serialized { in["Sprite"].as<std::string>() };
    auto color_serialized  { in["Color"].as<std::string>()  };
    uint32_t color_tmp {0};
    try { sprite.Reset(sprite_serialized); }
    catch (const std::runtime_error &) {
      VOLT_LOG_WARN("{} :: Sprite couldn't get resolved, falling back to default", func_name);
    }
    if (1 != std::sscanf(color_serialized.c_str(), "%x", &color_tmp)) {
      VOLT_LOG_ERROR("{} :: `{}.Color` value format not valid",
                     func_name, SpriteRendererComponent::cmp_name);
      return false;
    }
    color = color_tmp;
    return true;
  }

  void SpriteRendererComponent::Draw(void) {
    static bool is_first_time { true };
    static std::array<char, 32> sprite_path { "default" };
    static ImVec4 sprite_color {1, 1, 1, 1};
    if (is_first_time) {
      size_t len { std::min(sprite.name().size(), sprite_path.size() - 1) };
      std::copy_n(sprite.name().begin(), len, sprite_path.begin());
      sprite_path[len] = 0;
      Vector4 c { ColorNormalize(GetColor(color)) };
      sprite_color.x = c.x;
      sprite_color.y = c.y;
      sprite_color.z = c.z;
      sprite_color.w = c.w;
      is_first_time = false;
    }
    if (ImGui::CollapsingHeader(SpriteRendererComponent::cmp_name)) {
      ImGui::InputText("Sprite", sprite_path.data(), sprite_path.size());
      try { sprite.Reset(std::string(sprite_path.data())); }
      catch (const std::runtime_error &) {
        ImGui::TextColored(ImVec4{1, 0.25f, 0.25f, 1}, "Path doesn't resolve to asset");
      }
      if (ImGui::ColorEdit4("Color", &sprite_color.x)) {
        Vector4 c {sprite_color.x * 255, sprite_color.y * 255, sprite_color.z * 255, sprite_color.w * 255};
        color = (std::lround(c.x) << 24) | (std::lround(c.y) << 16) | (std::lround(c.z) << 8) | std::lround(c.w);
      }
    }
  }
}
