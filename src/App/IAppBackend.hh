#pragma once

namespace volt::app {
  struct IAppBackend {
    virtual ~IAppBackend(void) = default;
    virtual AppSpec Init(void) = 0;
    virtual void Start(runtime::Scene &s) = 0;
    virtual void Update(runtime::Scene &s) = 0;
  };
}
