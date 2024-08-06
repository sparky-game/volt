#include <imgui.h>
#include "SpriteRendererComponent.hh"

namespace volt::renderer {
  SpriteRendererComponent::SpriteRendererComponent(const Sprite &s)
    : sprite{s}
  {}

  void SpriteRendererComponent::DrawDetails(void) {
    if (ImGui::CollapsingHeader("Sprite Renderer")) {
      // ...
    }
  }
}
