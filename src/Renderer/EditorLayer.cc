#include <imgui.h>
#include <rlImGui.h>
#include "Window.hh"
#include "EditorLayer.hh"
#include "SpriteRendererComponent.hh"
#include "../Runtime/TransformComponent.hh"
#include "../Runtime/Rigidbody2DComponent.hh"

namespace volt::renderer {
  void EditorLayer::drawMenubar(void) noexcept {
    if (ImGui::BeginMainMenuBar()) {
      if (ImGui::BeginMenu("File")) {
        if (ImGui::MenuItem("Exit", "Ctrl+Q")) m_closeRequested = true;
        ImGui::EndMenu();
      }
      ImGui::EndMainMenuBar();
    }
  }

  void EditorLayer::drawControls(runtime::Scene &s) noexcept {
    if (ImGui::Begin("Controls", nullptr, ImGuiWindowFlags_NoTitleBar)) {
      if (s.IsRunning()) {
        if (ImGui::Button("Pause")) {
          s.Pause();
        }
      }
      else if (ImGui::Button("Play")) {
        s.Play();
      }
      ImGui::SameLine();
      if (ImGui::Button("Stop")) {
        s.Stop();
      }
    }
    ImGui::End();
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
    static std::array<char, 32> entity_name { "Entity" };
    if (ImGui::Begin("Hierarchy")) {
      if (ImGui::BeginPopupContextWindow()) {
        if (ImGui::Button("New entity ...")) {
          ImGui::OpenPopup("new_entity_ctx_menu");
        }
        if (ImGui::BeginPopup("new_entity_ctx_menu")) {
          ImGui::Text("Tag");
          ImGui::InputText("##new_entity", entity_name.data(), entity_name.size());
          if (not entity_name.empty() and ImGui::Button("Create")) {
            s.CreateEntity(std::string(entity_name.data()));
            ImGui::CloseCurrentPopup();
          }
          ImGui::EndPopup();
        }
        ImGui::EndPopup();
      }
      s.ForAll<runtime::TagComponent>([&](auto e, auto &t) {
        if (ImGui::Selectable(t.tag.c_str(), m_selectedEntityID == e.GetID())) {
          m_selectedEntityID = e.GetID();
        }
        if (ImGui::BeginPopupContextItem()) {
          if (ImGui::Button("Delete")) {
            s.DestroyEntity(e);
          }
          if (ImGui::Button("Rename ...")) {
            ImGui::OpenPopup("rename_entity_ctx_menu");
          }
          if (ImGui::BeginPopup("rename_entity_ctx_menu")) {
            ImGui::Text("Tag");
            ImGui::InputText("##rename_entity", entity_name.data(), entity_name.size());
            if (not entity_name.empty() and ImGui::Button("Rename")) {
              e.template GetComponent<runtime::TagComponent>().tag = std::string(entity_name.data());
              ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
          }
          ImGui::EndPopup();
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
        if (e->HasComponent<runtime::Rigidbody2DComponent>()) {
          e->GetComponent<runtime::Rigidbody2DComponent>().DrawDetails();
        }
        if (e->HasComponent<SpriteRendererComponent>()) {
          e->GetComponent<SpriteRendererComponent>().DrawDetails();
        }
        if (ImGui::Button("Add component")) {
          ImGui::OpenPopup("add_cmp_ctx_menu");
        }
        if (ImGui::BeginPopup("add_cmp_ctx_menu")) {
          ImGui::SeparatorText("Search");
          if (not e->HasComponent<runtime::Rigidbody2DComponent>() and ImGui::Selectable(runtime::Rigidbody2DComponent::cmp_name)) {
            e->AddComponent<runtime::Rigidbody2DComponent>();
          }
          ImGui::EndPopup();
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
    static std::array<float, 100> frametime_buf;
    static size_t i {0};
    static float fps {0};
    fps = ImGui::GetIO().Framerate;
    frametime_buf[i] = 1e3 / fps;
    if (ImGui::Begin("Stats")) {
      ImGui::PlotLines("",
                       frametime_buf.data(),
                       frametime_buf.size(),
                       i,
                       TextFormat("FPS: %.1f\nFrametime: %.3f", fps, frametime_buf[i]),
                       frametime_buf[i] - 40, frametime_buf[i] + 40,
                       ImVec2{0, 80});
    }
    ImGui::End();
    i = (i + 1) % frametime_buf.max_size();
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
    drawControls(s);
    drawScene(w);
    drawHierarchy(s);
    drawInspector(s);
    drawProject();
    drawStats();
    rlImGuiEnd();
  }
}
