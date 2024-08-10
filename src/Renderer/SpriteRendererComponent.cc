#include <imgui.h>
#include "SpriteRendererComponent.hh"

namespace volt::renderer {
  SpriteRendererComponent::SpriteRendererComponent(Sprite &&s) noexcept
    : sprite{std::move(s)}
  {}

  void SpriteRendererComponent::DrawDetails(void) {
    if (ImGui::CollapsingHeader("Sprite Renderer")) {
      // ...
    }
  }
}
