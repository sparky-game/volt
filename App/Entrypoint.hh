#pragma once

// Components
#include "../Runtime/InputComponent.hh"
#include "../Runtime/PhysicsComponent.hh"
#include "../Renderer/RenderComponent.hh"
#include "../Runtime/BehaviourComponent.hh"

// Behaviours
#include "../Runtime/BehaviourBounce.hh"

// Systems
#include "../Runtime/InputSystem.hh"
#include "../Runtime/PhysicsSystem.hh"
#include "../Renderer/RenderSystem.hh"
#include "../Runtime/BehaviourSystem.hh"
#include "../Renderer/PreRenderSystem.hh"

// App
#include "AppSpec.hh"
#include "IAppBackend.hh"

extern volt::app::IAppBackend *CreateVoltApp(void);

int main(void) {
  // App creation
  auto *app { CreateVoltApp() };
  // App initialization
  auto app_spec { app->Initialize() };
  // Engine systems startup
  volt::renderer::RenderSystem renderer{{
      app_spec.renderer.width,
      app_spec.renderer.height,
      app_spec.renderer.name,
      app_spec.renderer.max_fps
    }
  };
  volt::renderer::PreRenderSystem pre_renderer;
  volt::runtime::BehaviourSystem behaviour;
  volt::runtime::PhysicsSystem physics;
  volt::runtime::InputSystem input;
  // Scene creation
  volt::runtime::Scene scene;
  // App `OnStart` callback
  app->Start(scene);
  // Engine loop
  while (renderer.IsRunning()) {
    auto t { volt::core::GetTimepoint() };
    input.Update(scene);
    behaviour.Update(scene);
    physics.Update(scene);
    pre_renderer.Update(scene);
    renderer.Update(scene);
    renderer.WaitIdle(t);
  }
  // App destruction
  delete app;
}
