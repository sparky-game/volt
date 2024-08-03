#include <format>
#include <fstream>
#include "Scene.hh"
#include <filesystem>
#include <yaml-cpp/yaml.h>
#include "SceneSerializer.hh"
#include "../Core/LogSystem.hh"
#include "TransformComponent.hh"

namespace volt::runtime {
  static inline void SerializeEntity(YAML::Emitter &out, Entity &e) {
    out << YAML::BeginMap;
    out << YAML::Key << "ID"  << YAML::Value << e.GetID();
    out << YAML::Key << "Tag" << YAML::Value << e.GetName();
    if (e.HasComponent<TransformComponent>()) {
      auto &t { e.GetComponent<TransformComponent>() };
      out << YAML::Key << "Transform" << YAML::BeginMap;
      out << YAML::Key << "Position" << YAML::Value << std::format("({:.3f}, {:.3f})", t.position_x, t.position_y);
      out << YAML::EndMap;
    }
    out << YAML::EndMap;
  }

  SceneSerializer::SceneSerializer(Scene *scene)
    : m_scene{scene}
  {}

  void SceneSerializer::Serialize(const std::filesystem::path &path) {
    std::ofstream ofs { path };
    if (not ofs) {
      VOLT_LOG_ERROR("volt::runtime::SceneSerializer({})::Serialize('{}') :: unable to open file for writing",
                     fmt::ptr(m_scene), std::string(path));
      return;
    }
    YAML::Emitter out;
    out << YAML::BeginMap;
    out << YAML::Key << "Scene"    << YAML::Value << "Untitled";
    out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
    m_scene->ForAll<runtime::TagComponent>([&](auto e, auto &) {
      SerializeEntity(out, e);
    });
    out << YAML::EndSeq << YAML::EndMap;
    ofs << out.c_str();
  }
}
