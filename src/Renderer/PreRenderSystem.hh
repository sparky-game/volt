#pragma once

#include "../Runtime/Scene.hh"

namespace volt::renderer {
  struct PreRenderSystem {
    PreRenderSystem(void);
    PreRenderSystem(const PreRenderSystem &) = delete;
    PreRenderSystem(PreRenderSystem &&) = delete;
    PreRenderSystem &operator=(const PreRenderSystem &) = delete;
    PreRenderSystem &operator=(PreRenderSystem &&) = delete;
    ~PreRenderSystem(void);
    void Update(runtime::Scene &s);
  };
}
