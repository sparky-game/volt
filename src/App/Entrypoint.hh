#pragma once

// Components
#include "../Runtime/InputComponent.hh"
#include "../Runtime/TransformComponent.hh"
#include "../Runtime/BehaviourComponent.hh"
#include "../Runtime/Rigidbody2DComponent.hh"
#include "../Renderer/SpriteRendererComponent.hh"

// Behaviours
#include "../Runtime/BehaviourBounce.hh"

// Systems
#include "../Core/VFS.hh"
#include "../Core/LogSystem.hh"
#include "../Runtime/Project.hh"
#include "../Runtime/InputSystem.hh"
#include "../Runtime/PhysicsSystem.hh"
#include "../Renderer/RenderSystem.hh"
#include "../Runtime/BehaviourSystem.hh"
#include "../Runtime/SceneSerializer.hh"
#include "../Renderer/PreRenderSystem.hh"

// App
#include "AppSpec.hh"
#include "Goodbye.hh"
#include "IAppBackend.hh"

extern volt::app::IAppBackend *CreateVoltApp(void);

int main(void) {
  volt::core::LogSystem::Init();
  volt::core::VFS vfs;

  volt::app::Goodbye::Init();

  auto *app { CreateVoltApp() };
  auto app_spec { app->Init() };

  volt::renderer::RenderSystem renderer { app_spec.renderer };
  volt::renderer::PreRenderSystem pre_renderer { renderer };
  volt::runtime::BehaviourSystem behaviour;
  volt::runtime::PhysicsSystem physics;
  volt::runtime::InputSystem input;

  volt::runtime::Project proj { app_spec.project };

  auto &scene { *proj.CreateScene("Main") };
  app->Start(scene);
  if (not renderer.IsEditor()) scene.Play();

  while (renderer.IsRunning() and volt::app::Goodbye::IsAlive()) {
    auto t { volt::core::GetTimepoint() };
    if (scene.IsRunning()) {
      input.Update(scene);
      behaviour.Update(scene);
      physics.Update(scene);
    }
    pre_renderer.Update(scene);
    renderer.Update(scene);
    renderer.WaitIdle(t);
  }

  if (scene.IsRunning()) scene.Stop();

  app->Stop(scene);
  delete app;
}
