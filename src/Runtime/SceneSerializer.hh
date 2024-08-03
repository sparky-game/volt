#pragma once

namespace volt::runtime {
  class Scene;

  class SceneSerializer {
    Scene *m_scene;
  public:
    SceneSerializer(Scene *scene);
    SceneSerializer(const SceneSerializer &) = delete;
    SceneSerializer(SceneSerializer &&) = delete;
    SceneSerializer &operator=(const SceneSerializer &) = delete;
    SceneSerializer &operator=(SceneSerializer &&) = delete;
    void Serialize(const std::filesystem::path &path);
    bool Deserialize(const std::filesystem::path &path);
  };
}
