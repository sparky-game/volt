#include <imgui.h>
#include <rlImGui.h>
#include "Window.hh"
#include <ImGuizmo.h>
#include "EditorLayer.hh"
#include "../Core/LogSystem.hh"
#include "SpriteRendererComponent.hh"
#include "../Runtime/TransformComponent.hh"
#include "../Runtime/Rigidbody2DComponent.hh"

extern "C" {
  // NOTE: @raysan5 fixed this issue on raylib's commit `3801819` (2024/06/06).
  // Commit diff: https://github.com/raysan5/raylib/commit/38018192b8055024c4aa9b041943aa4e85bdd773
  // Issue: https://www.reddit.com/r/raylib/comments/1d8m52k/question_why_does_including_raymathh_make_my
#ifdef near
#undef near
#endif
#ifdef far
#undef far
#endif
#include <raymath.h>
}

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
        ImGui::SameLine();
        if (ImGui::Button("Stop")) {
          s.Stop();
        }
      }
      else if (ImGui::Button("Play")) {
        s.Play();
      }
    }
    ImGui::End();
  }

  void EditorLayer::drawScene(runtime::Scene &s, Window &w) const noexcept {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    if (ImGui::Begin("Scene")) {
      rlImGuiImageRenderTextureFit(w.GetEditorViewportFBO(), true);
    }

    // Gizmos
    auto e { s.FindEntityByID(m_selectedEntityID) };
    if (e and not s.IsRunning()) {
      auto &t { e->GetComponent<runtime::TransformComponent>() };
      ImVec2 win_size { ImGui::GetWindowSize() };
      ImGuizmo::SetOrthographic(true);
      ImGuizmo::SetDrawlist();
      ImGuizmo::SetRect(0, 0, win_size.x, win_size.y);
      static Matrix cameraView { MatrixIdentity() };
      static Matrix cameraProjection { MatrixIdentity() };
      static Matrix transform { MatrixTranslate(t.position.X(), t.position.Y(), 0) };
      transform.m12 = t.position.X();
      transform.m13 = t.position.Y();
      ImGuizmo::Manipulate(&cameraView.m0, &cameraProjection.m0, ImGuizmo::OPERATION::TRANSLATE, ImGuizmo::WORLD, &transform.m0);
      if (ImGuizmo::IsUsing()) {
        Vector3 position, rotation, scale;
        ImGuizmo::DecomposeMatrixToComponents(&transform.m0, &position.x, &rotation.x, &scale.x);
        t.position.X(position.x * win_size.x);
        t.position.Y(position.y * -win_size.y);
      }
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
          e->GetComponent<runtime::TransformComponent>().Draw();
        }
        if (e->HasComponent<runtime::Rigidbody2DComponent>()) {
          e->GetComponent<runtime::Rigidbody2DComponent>().Draw();
        }
        if (e->HasComponent<SpriteRendererComponent>()) {
          e->GetComponent<SpriteRendererComponent>().Draw();
        }
        if (ImGui::Button("Add component")) {
          ImGui::OpenPopup("add_cmp_ctx_menu");
        }
        if (ImGui::BeginPopup("add_cmp_ctx_menu")) {
          ImGui::SeparatorText("Search");
          if (not e->HasComponent<runtime::Rigidbody2DComponent>() and ImGui::Selectable(runtime::Rigidbody2DComponent::cmp_name)) {
            e->AddComponent<runtime::Rigidbody2DComponent>();
          }
          if (not e->HasComponent<SpriteRendererComponent>() and ImGui::Selectable(SpriteRendererComponent::cmp_name)) {
            e->AddComponent<SpriteRendererComponent>(Sprite{});
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
    constexpr auto config_filename { "volt.ini" };
    if (not std::filesystem::exists(config_filename) or not std::filesystem::is_regular_file(config_filename)) {
      if (not ChangeDirectory(GetApplicationDirectory())) {
        VOLT_LOG_WARN("volt::renderer::EditorLayer::Setup :: could not change CWD to Volt's editor binary directory");
        // TODO: download the file from the repo.
      }
      // TODO: check if it's present, if it's not then download it from the repo.
    }
    rlImGuiSetup(true);
    ImGuiIO &imgui_io { ImGui::GetIO() };
    imgui_io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    imgui_io.IniFilename = config_filename;
    imgui_io.LogFilename = nullptr;
    imgui_io.ConfigWindowsMoveFromTitleBarOnly = true;
  }

  void EditorLayer::Draw(runtime::Scene &s, Window &w) noexcept {
    static bool is_first_time { true };
    rlImGuiBegin();
    ImGuizmo::BeginFrame();
    ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());
    if (is_first_time) {
      ImGui::OpenPopup("Welcome");
      is_first_time = false;
    }
    if (ImGui::BeginPopupModal("Welcome", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
      ImGui::Text("Welcome to Volt!");
      ImGui::Separator();
      ImGui::Text("Please report bugs and issues to: https://github.com/sparky-game/volt/issues");
      if (ImGui::Button("OK")) ImGui::CloseCurrentPopup();
      ImGui::EndPopup();
    }
    ImGui::ShowDemoWindow();  // TEMPORARY DEMO
    drawMenubar();
    drawControls(s);
    drawScene(s, w);
    drawHierarchy(s);
    drawInspector(s);
    drawProject();
    drawStats();
    rlImGuiEnd();
  }
}
