#include <format>
#include <fstream>
#include "Scene.hh"
#include <filesystem>
#include <yaml-cpp/yaml.h>
#include "SceneSerializer.hh"
#include "../Core/LogSystem.hh"
#include "TransformComponent.hh"
#include "Rigidbody2DComponent.hh"

namespace volt::runtime {
  static inline void SerializeEntity(YAML::Emitter &out, Entity &e) {
    out << YAML::BeginMap;
    out << YAML::Key << "ID"  << YAML::Value << e.GetID();
    out << YAML::Key << "Tag" << YAML::Value << e.GetName();
    if (e.HasComponent<TransformComponent>()) {
      auto &t { e.GetComponent<TransformComponent>() };
      out << YAML::Key << TransformComponent::cmp_name << YAML::BeginMap;
      out << YAML::Key << "Position" << YAML::Value << std::format("({:.3f}, {:.3f})", t.position_x, t.position_y);
      out << YAML::EndMap;
    }
    if (e.HasComponent<Rigidbody2DComponent>()) {
      auto &rb { e.GetComponent<Rigidbody2DComponent>() };
      out << YAML::Key << Rigidbody2DComponent::cmp_name << YAML::BeginMap;
      out << YAML::Key << "Velocity" << YAML::Value << std::format("({:.3f}, {:.3f})", rb.velocity_x, rb.velocity_y);
      out << YAML::EndMap;
    }
    out << YAML::EndMap;
  }

  static inline bool DeserializeEntity(auto e, Scene *s, auto &path) {
    auto id { e["ID"].template as<core::SnowflakeID::value_type>() };
    auto tag { e["Tag"].template as<std::string>() };
    auto e_deserialized { s->CreateEntity(core::SnowflakeID(id), tag) };
    auto transform { e[TransformComponent::cmp_name] };
    if (transform) {
      auto transform_position_str { transform["Position"].template as<std::string>() };
      float transform_position_x {0}, transform_position_y {0};
      if (2 != std::sscanf(transform_position_str.c_str(), "(%f, %f)", &transform_position_x, &transform_position_y)) {
        VOLT_LOG_ERROR("volt::runtime::SceneSerializer({})::Deserialize('{}') :: `{}.Position` value format not valid",
                       fmt::ptr(s), std::string(path), TransformComponent::cmp_name);
        return false;
      }
      auto &transform_cmp { e_deserialized.template GetComponent<TransformComponent>() };
      transform_cmp.position_x = transform_position_x;
      transform_cmp.position_y = transform_position_y;
    }
    auto rigidbody2d { e[Rigidbody2DComponent::cmp_name] };
    if (rigidbody2d) {
      auto rigidbody2d_velocity_str { rigidbody2d["Velocity"].template as<std::string>() };
      float rigidbody2d_velocity_x {0}, rigidbody2d_velocity_y {0};
      if (2 != std::sscanf(rigidbody2d_velocity_str.c_str(), "(%f, %f)", &rigidbody2d_velocity_x, &rigidbody2d_velocity_y)) {
        VOLT_LOG_ERROR("volt::runtime::SceneSerializer({})::Deserialize('{}') :: `{}.Velocity` value format not valid",
                       fmt::ptr(s), std::string(path), Rigidbody2DComponent::cmp_name);
        return false;
      }
      e_deserialized.template AddComponent<Rigidbody2DComponent>(rigidbody2d_velocity_x, rigidbody2d_velocity_y);
    }
    return true;
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
        if (not DeserializeEntity(e, m_scene, path)) return false;
      }
    }
    VOLT_LOG_INFO("Scene loaded from file successfully (`{}`)", std::string(path));
    return true;
  }
}
