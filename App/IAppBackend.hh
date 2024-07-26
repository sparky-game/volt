#pragma once

namespace volt::app {
  struct IAppBackend {
    virtual ~IAppBackend(void) = default;
    virtual AppSpec Initialize(void) = 0;
    virtual void Start(runtime::Scene &s) = 0;
  };
}
