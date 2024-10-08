#include "Scene.hh"
#include "../Core/LogSystem.hh"
#include "TransformComponent.hh"

namespace volt::runtime {
  Entity::Entity(EID id, Scene *scene)
    : m_id{id}, m_scene{scene}
  {}

  Scene::Scene(const std::string &name)
    : m_name{name}, m_running{false}
  {}

  Scene::~Scene(void) {
    m_registry.clear();
    VOLT_LOG_INFO("Scene: destroyed successfully");
  }

  Entity Scene::CreateEntity(const std::string &name) {
    return CreateEntity(core::SnowflakeID(), name);
  }

  Entity Scene::CreateEntity(core::SnowflakeID id, const std::string &name) {
    Entity e { m_registry.create(), this };
    e.AddComponent<IDComponent>(id);
    e.AddComponent<TagComponent>(name.empty() ? "Entity" : name);
    e.AddComponent<TransformComponent>();
    m_ids[id] = e;
    VOLT_LOG_INFO("Scene: Entity created [{}|{}]", static_cast<core::SnowflakeID::value_type>(id), name);
    return e;
  }

  void Scene::DestroyEntity(Entity e) {
    m_ids.erase(e.GetID());
    m_registry.destroy(e);
    VOLT_LOG_INFO("Scene: Entity destroyed [{}|{}]", e.GetID(), e.GetName());
  }

  std::optional<Entity> Scene::FindEntityByID(core::SnowflakeID::value_type id) {
    if (m_ids.find(id) != m_ids.end()) return Entity{ m_ids.at(id), this };
    return {};
  }

  std::optional<Entity> Scene::FindEntityByName(const std::string &name) {
    auto view { m_registry.view<TagComponent>() };
    for (auto e : view) {
      auto &t { view.get<TagComponent>(e) };
      if (t.tag == name) return Entity{ e, this };
    }
    return {};
  }

  void Scene::Play(void) noexcept {
    if (not m_running) m_running = true;
  }

  void Scene::Pause(void) noexcept {
    if (m_running) m_running = false;
  }

  void Scene::Stop(void) noexcept {
    Pause();
    // TODO: figure out how to reset/rewind the scene
  }
}
