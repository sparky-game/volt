#include <volt.hh>

#define XSTR(s) STR(s)
#define STR(s) #s

#define NAME "Volt v" XSTR(VOLT_VERSION)

struct Editor : public volt::app::IAppBackend {
  volt::app::AppSpec Init(void) final {
    return {
      .renderer {
        .width     = 1280,
        .height    = 720,
        .name      = NAME,
        .max_fps   = 75,
        .is_editor = true
      },
      .project {
        .name = NAME,
        .path = "."
      }
    };
  }

  void Start(volt::runtime::Scene &s) final {
    volt::runtime::SceneSerializer ss { &s };
    ss.Deserialize("scene.yaml");
  }

  void Stop(volt::runtime::Scene &s) final {
    volt::runtime::SceneSerializer ss { &s };
    ss.Serialize("scene.yaml");
  }
};

volt::app::IAppBackend *CreateVoltApp(void) { return new Editor; }
