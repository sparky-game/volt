#pragma once

namespace volt::app {
  struct AppSpec {
    renderer::RenderSystemSpec renderer;
    runtime::ProjectSpec project;
  };
}
