#include <imgui.h>
#include <rlImGui.h>
#include "Window.hh"
#include "RenderSystem.hh"
#include "RenderComponent.hh"
#include "../Core/LogSystem.hh"
#include "../Runtime/TransformComponent.hh"

static volt::core::SnowflakeID::value_type s_selectedEntityID {0};

namespace volt::renderer {
  void RenderSystem::editorLayerSetup(void) const {
    rlImGuiSetup(true);
    ImGuiIO &imgui_io { ImGui::GetIO() };
    imgui_io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    // imgui_io.IniFilename = nullptr;
    imgui_io.LogFilename = nullptr;
    imgui_io.ConfigWindowsMoveFromTitleBarOnly = true;
  }

  void RenderSystem::editorLayerDraw(runtime::Scene &s) {
    rlImGuiBegin();
    ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());
    ImGui::ShowDemoWindow();  // TEMPORARY DEMO
    editorLayerDrawMenubar();
    editorLayerDrawScene();
    editorLayerDrawHierarchy(s);
    editorLayerDrawInspector(s);
    editorLayerDrawProject();
    rlImGuiEnd();
    editorLayerDrawStats();
  }

  void RenderSystem::editorLayerDrawMenubar(void) {
    if (ImGui::BeginMainMenuBar()) {
      if (ImGui::BeginMenu("File")) {
        if (ImGui::MenuItem("Exit")) m_closeRequested = true;
        ImGui::EndMenu();
      }
      ImGui::EndMainMenuBar();
    }
  }

  void RenderSystem::editorLayerDrawScene(void) {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    if (ImGui::Begin("Scene")) {
      rlImGuiImageRenderTextureFit(m_window.GetEditorViewportFBO(), true);
    }
    ImGui::End();
    ImGui::PopStyleVar();
  }

  void RenderSystem::editorLayerDrawHierarchy(runtime::Scene &s) {
    if (ImGui::Begin("Hierarchy")) {
      s.ForAll<runtime::TagComponent>([](auto e, auto &t) {
        if (ImGui::Selectable(t.tag.c_str(), s_selectedEntityID == e.GetID())) {
          s_selectedEntityID = e.GetID();
        }
      });
    }
    ImGui::End();
  }

  void RenderSystem::editorLayerDrawInspector(runtime::Scene &s) {
    if (ImGui::Begin("Inspector")) {
      auto e { s.FindEntityByID(s_selectedEntityID) };
      if (e) {
        if (e->HasComponent<runtime::TransformComponent>()) {
          e->GetComponent<runtime::TransformComponent>().DrawDetails();
        }
      }
    }
    ImGui::End();
  }

  void RenderSystem::editorLayerDrawProject(void) {
    if (ImGui::Begin("Project")) {
      // ...
    }
    ImGui::End();
  }

  void RenderSystem::editorLayerDrawStats(void) {
    DrawText(TextFormat("FPS: %u (%.1f ms)", GetFPS(), GetFrameTime() * 1000),
             GetScreenWidth() - 190,
             GetScreenHeight() - 40,
             14, LIGHTGRAY);
  }

  RenderSystem::RenderSystem(const RenderSystemSpec &spec)
    : m_spec{spec}, m_window{m_spec}, m_minFrameTime{static_cast<int64_t>(1e9) / m_spec.max_fps}, m_closeRequested{false}
  {
    if (IsEditor()) editorLayerSetup();
    VOLT_LOG_INFO("volt::renderer::RenderSystem :: created successfully");
  }

  RenderSystem::~RenderSystem(void) {
    VOLT_LOG_INFO("volt::renderer::~RenderSystem :: destroyed successfully");
  }

  void RenderSystem::Update(runtime::Scene &s) {
    if (IsEditor()) {
      BeginTextureMode(*m_window.GetEditorViewportFBO());
      ClearBackground(DARKGRAY);
    }
    s.ForAll<RenderComponent>([this]([[maybe_unused]] auto e, auto &r) {
      m_window.Draw(r.sprite, r.position_x, r.position_y);
    });
    if (IsEditor()) {
      EndTextureMode();
      editorLayerDraw(s);
    }
    m_window.Update();
  }

  bool RenderSystem::IsRunning(void) const {
    if (m_closeRequested) return false;
    return m_window.IsOpen();
  }

  void RenderSystem::WaitIdle(const core::Timepoint &t) const {
    while ((core::GetTimepoint() - t).count() < m_minFrameTime);
  }
}
