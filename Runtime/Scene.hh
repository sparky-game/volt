#pragma once

#include "IDComponent.hh"
#include "TagComponent.hh"
#include <entt/src/entt/entt.hpp>

namespace volt::runtime {
  class Scene;

  using EID = entt::entity;

  class Entity {
    EID m_id;
    Scene *m_scene;
  public:
    Entity(EID id, Scene *scene);
    inline const core::SnowflakeID &GetID(void)   { return GetComponent<IDComponent>().id; }
    inline const std::string &GetName(void) { return GetComponent<TagComponent>().tag; }
    template <typename T>
    bool HasComponent(void) const;
    template <typename T, typename... Args>
    T &AddComponent(Args &&... args);
    template <typename T>
    void RemoveComponent(void);
    template <typename T>
    T &GetComponent(void) const;
    inline operator EID(void) const noexcept { return m_id; }
  };

  class Scene {
    friend class Entity;
    entt::registry m_registry;
    std::unordered_map<core::SnowflakeID::value_type, EID> m_ids;
  public:
    Scene(void) = default;
    Scene(const Scene &) = delete;
    Scene(Scene &&) = delete;
    Scene &operator=(const Scene &) = delete;
    Scene &operator=(Scene &&) = delete;
    Entity CreateEntity(const std::string &name = std::string());
    Entity CreateEntity(core::SnowflakeID id, const std::string &name = std::string());
    void DestroyEntity(Entity e);
    template <typename... Comps, typename F>
    inline void ForAll(F callback) {
      auto view { m_registry.view<Comps...>() };
      for (auto e : view) {
        callback(Entity{ e, this }, view.template get<Comps>(e)...);
      }
    }
    std::optional<Entity> FindEntityByID(const core::SnowflakeID &id);
    std::optional<Entity> FindEntityByName(const std::string &name);
  };

  template <typename T>
  inline bool Entity::HasComponent(void) const {
    return m_scene->m_registry.any_of<T>(m_id);
  }

  template <typename T, typename... Args>
  inline T &Entity::AddComponent(Args &&... args) {
    assert(not HasComponent<T>());
    return m_scene->m_registry.emplace<T>(m_id, std::forward<Args>(args)...);
  }

  template <typename T>
  inline void Entity::RemoveComponent(void) {
    assert(HasComponent<T>());
    m_scene->m_registry.remove<T>(m_id);
  }

  template <typename T>
  inline T &Entity::GetComponent(void) const {
    assert(HasComponent<T>());
    return m_scene->m_registry.get<T>(m_id);
  }
}
