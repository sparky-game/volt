#pragma once

// Components
#include "../Runtime/InputComponent.hh"
#include "../Renderer/RenderComponent.hh"
#include "../Runtime/TransformComponent.hh"
#include "../Runtime/BehaviourComponent.hh"
#include "../Runtime/Rigidbody2DComponent.hh"

// Behaviours
#include "../Runtime/BehaviourBounce.hh"

// Systems
#include "../Core/LogSystem.hh"
#include "../Runtime/InputSystem.hh"
#include "../Runtime/PhysicsSystem.hh"
#include "../Renderer/RenderSystem.hh"
#include "../Runtime/BehaviourSystem.hh"
#include "../Renderer/PreRenderSystem.hh"

// App
#include "AppSpec.hh"
#include "IAppBackend.hh"

#include "../Runtime/SceneSerializer.hh"

extern volt::app::IAppBackend *CreateVoltApp(void);

int main(void) {
  volt::core::LogSystem::Init();

  auto *app { CreateVoltApp() };
  auto app_spec { app->Init() };

  volt::renderer::RenderSystem renderer { app_spec.renderer };
  volt::renderer::PreRenderSystem pre_renderer { renderer };
  volt::runtime::BehaviourSystem behaviour;
  volt::runtime::PhysicsSystem physics;
  volt::runtime::InputSystem input;

  volt::runtime::Scene scene;
  app->Start(scene);

  while (renderer.IsRunning()) {
    auto t { volt::core::GetTimepoint() };
    input.Update(scene);
    behaviour.Update(scene);
    physics.Update(scene);
    pre_renderer.Update(scene);
    app->Update(scene);
    renderer.Update(scene);
    renderer.WaitIdle(t);
  }

  app->Stop(scene);
  delete app;
}
