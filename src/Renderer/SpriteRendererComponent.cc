#include <array>
#include <imgui.h>
#include "SpriteRendererComponent.hh"

namespace volt::renderer {
  SpriteRendererComponent::SpriteRendererComponent(Sprite &&s) noexcept
    : sprite{std::move(s)}
  {}

  void SpriteRendererComponent::DrawDetails(void) {
    static std::array<char, 32> sprite_path;
    if (ImGui::CollapsingHeader(SpriteRendererComponent::cmp_name)) {
      ImGui::InputText("Sprite", sprite_path.data(), sprite_path.size());
      try { sprite.Reset(std::string(sprite_path.data())); }
      catch (const std::runtime_error &) {
        ImGui::TextColored(ImVec4{1, 0.25f, 0.25f, 1}, "Path doesn't resolve to asset");
      }
    }
  }
}
