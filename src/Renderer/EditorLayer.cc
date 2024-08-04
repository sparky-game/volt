#include <imgui.h>
#include <rlImGui.h>
#include "Window.hh"
#include "EditorLayer.hh"
#include "../Runtime/TransformComponent.hh"

namespace volt::renderer {
  void EditorLayer::drawMenubar(void) noexcept {
    if (ImGui::BeginMainMenuBar()) {
      if (ImGui::BeginMenu("File")) {
        if (ImGui::MenuItem("Exit")) m_closeRequested = true;
        ImGui::EndMenu();
      }
      ImGui::EndMainMenuBar();
    }
  }

  void EditorLayer::drawScene(Window &w) const noexcept {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    if (ImGui::Begin("Scene")) {
      rlImGuiImageRenderTextureFit(w.GetEditorViewportFBO(), true);
    }
    ImGui::End();
    ImGui::PopStyleVar();
  }

  void EditorLayer::drawHierarchy(runtime::Scene &s) noexcept {
    if (ImGui::Begin("Hierarchy")) {
      s.ForAll<runtime::TagComponent>([this](auto e, auto &t) {
        if (ImGui::Selectable(t.tag.c_str(), m_selectedEntityID == e.GetID())) {
          m_selectedEntityID = e.GetID();
        }
      });
    }
    ImGui::End();
  }

  void EditorLayer::drawInspector(runtime::Scene &s) const noexcept {
    if (ImGui::Begin("Inspector")) {
      auto e { s.FindEntityByID(m_selectedEntityID) };
      if (e) {
        if (e->HasComponent<runtime::TransformComponent>()) {
          e->GetComponent<runtime::TransformComponent>().DrawDetails();
        }
      }
    }
    ImGui::End();
  }

  void EditorLayer::drawProject(void) const noexcept {
    if (ImGui::Begin("Project")) {
      // ...
    }
    ImGui::End();
  }

  void EditorLayer::drawStats(void) const noexcept {
    DrawText(TextFormat("FPS: %u (%.1f ms)", GetFPS(), GetFrameTime() * 1000),
             GetScreenWidth() - 190,
             GetScreenHeight() - 40,
             14, LIGHTGRAY);
  }

  void EditorLayer::Setup(void) const noexcept {
    rlImGuiSetup(true);
    ImGuiIO &imgui_io { ImGui::GetIO() };
    imgui_io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    // imgui_io.IniFilename = nullptr;
    imgui_io.LogFilename = nullptr;
    imgui_io.ConfigWindowsMoveFromTitleBarOnly = true;
  }

  void EditorLayer::Draw(runtime::Scene &s, Window &w) noexcept {
    rlImGuiBegin();
    ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());
    ImGui::ShowDemoWindow();  // TEMPORARY DEMO
    drawMenubar();
    drawScene(w);
    drawHierarchy(s);
    drawInspector(s);
    drawProject();
    rlImGuiEnd();
    drawStats();
  }
}
