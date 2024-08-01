#include <volt.hh>

#define XSTR(s) STR(s)
#define STR(s) #s

struct Editor : public volt::app::IAppBackend {
  volt::app::AppSpec Init(void) final {
    return {
      .renderer {
        .width     = 1280,
        .height    = 720,
        .name      = "Volt v" XSTR(VOLT_VERSION),
        .max_fps   = 75,
        .is_editor = true
      }
    };
  }

  void Start(volt::runtime::Scene &) final {
    // ...
  }

  void Update(volt::runtime::Scene &) final {
    // ...
  }
};

volt::app::IAppBackend *CreateVoltApp(void) { return new Editor; }
