#pragma once

#include "../Runtime/Scene.hh"

namespace volt::renderer {
  struct PreRenderSystem {
    void Update(runtime::Scene &s);
  };
}
