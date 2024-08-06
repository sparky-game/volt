#include <fstream>
#include "Scene.hh"
#include <filesystem>
#include <yaml-cpp/yaml.h>
#include "SceneSerializer.hh"
#include "../Core/LogSystem.hh"
#include "TransformComponent.hh"
#include "Rigidbody2DComponent.hh"

namespace volt::runtime {
  static inline void SerializeEntity(auto &out, Entity &e) {
    out << YAML::BeginMap;
    out << YAML::Key << "ID"  << YAML::Value << e.GetID();
    out << YAML::Key << "Tag" << YAML::Value << e.GetName();
    if (e.HasComponent<TransformComponent>()) {
      e.GetComponent<TransformComponent>().Serialize(out);
    }
    if (e.HasComponent<Rigidbody2DComponent>()) {
      e.GetComponent<Rigidbody2DComponent>().Serialize(out);
    }
    out << YAML::EndMap;
  }

  static inline bool DeserializeEntity(Scene *s, auto &in) {
    auto id { in["ID"].template as<core::SnowflakeID::value_type>() };
    auto tag { in["Tag"].template as<std::string>() };
    auto e { s->CreateEntity(core::SnowflakeID(id), tag) };
    auto in_transform { in[TransformComponent::cmp_name] };
    if (in_transform and not e.template GetComponent<TransformComponent>().Deserialize(in_transform)) return false;
    auto in_rigidbody2d { in[Rigidbody2DComponent::cmp_name] };
    if (in_rigidbody2d) {
      auto &rb { e.template AddComponent<Rigidbody2DComponent>() };
      if (not rb.Deserialize(in_rigidbody2d)) return false;
    }
    return true;
  }

  SceneSerializer::SceneSerializer(Scene *s)
    : m_scene{s}
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
    VOLT_LOG_INFO("Scene saved to file successfully (`{}`)", std::string(path));
  }

  bool SceneSerializer::Deserialize(const std::filesystem::path &path) {
    std::ifstream ifs { path };
    if (not ifs) {
      VOLT_LOG_ERROR("volt::runtime::SceneSerializer({})::Deserialize('{}') :: unable to open file for reading",
                     fmt::ptr(m_scene), std::string(path));
      return false;
    }
    std::stringstream ss;
    ss << ifs.rdbuf();
    YAML::Node data { YAML::Load(ss.str()) };
    if (not data["Scene"]) {
      VOLT_LOG_ERROR("volt::runtime::SceneSerializer({})::Deserialize('{}') :: file format not valid",
                     fmt::ptr(m_scene), std::string(path));
      return false;
    }
    auto entities { data["Entities"] };
    if (entities) {
      for (auto e : entities) {
        if (not DeserializeEntity(m_scene, e)) return false;
      }
    }
    VOLT_LOG_INFO("Scene loaded from file successfully (`{}`)", std::string(path));
    return true;
  }
}
