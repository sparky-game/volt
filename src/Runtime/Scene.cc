#include "Scene.hh"
#include "TransformComponent.hh"

namespace volt::runtime {
  Entity::Entity(EID id, Scene *scene)
    : m_id{id}, m_scene{scene}
  {}

  Entity Scene::CreateEntity(const std::string &name) {
    return CreateEntity(core::SnowflakeID(), name);
  }

  Entity Scene::CreateEntity(core::SnowflakeID id, const std::string &name) {
    Entity e { m_registry.create(), this };
    e.AddComponent<IDComponent>(id);
    auto &t { e.AddComponent<TagComponent>() };
    t.tag = name.empty() ? "Entity" : name;
    e.AddComponent<TransformComponent>();
    m_ids[id] = e;
    return e;
  }

  void Scene::DestroyEntity(Entity e) {
    m_ids.erase(e.GetID());
    m_registry.destroy(e);
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
}
