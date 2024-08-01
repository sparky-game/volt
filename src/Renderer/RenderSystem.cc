#include <imgui.h>
#include <rlImGui.h>
#include "Window.hh"
#include "RenderSystem.hh"
#include "RenderComponent.hh"
#include "../Core/LogSystem.hh"

namespace volt::renderer {
  void RenderSystem::editorLayerSetup(void) const {
    rlImGuiSetup(true);
    ImGuiIO &imgui_io { ImGui::GetIO() };
    imgui_io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    imgui_io.IniFilename = nullptr;
    imgui_io.LogFilename = nullptr;
    imgui_io.ConfigWindowsMoveFromTitleBarOnly = true;
  }

  void RenderSystem::editorLayerDraw(void) {
    rlImGuiBegin();
    ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());
    if (ImGui::BeginMainMenuBar()) {
      if (ImGui::BeginMenu("File")) {
        if (ImGui::MenuItem("Exit")) m_closeRequested = true;
        ImGui::EndMenu();
      }
      ImGui::EndMainMenuBar();
    }
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    if (ImGui::Begin("Scene")) {
      rlImGuiImageRenderTextureFit(m_window.getEditorViewportFBO(), true);
    }
    ImGui::End();
    ImGui::PopStyleVar();
    rlImGuiEnd();
  }

  RenderSystem::RenderSystem(const RenderSystemSpec &spec)
    : m_spec{spec}, m_window{m_spec}, m_minFrameTime{static_cast<int64_t>(1e9) / m_spec.max_fps}, m_closeRequested{false}
  {
    if (m_spec.is_editor) editorLayerSetup();
    VOLT_LOG_INFO("volt::renderer::RenderSystem :: created successfully");
  }

  RenderSystem::~RenderSystem(void) {
    VOLT_LOG_INFO("volt::renderer::~RenderSystem :: destroyed successfully");
  }

  void RenderSystem::Update(runtime::Scene &s) {
    m_window.Clear(0);
    s.ForAll<RenderComponent>([this]([[maybe_unused]] auto e, auto &r) {
      m_window.Draw(r.sprite, r.position_x, r.position_y);
    });
    if (m_spec.is_editor) editorLayerDraw();
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
