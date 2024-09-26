#pragma once

#include <optional>
#include <entt/entt.hpp>
#include <box2d/box2d.h>
#include "IDComponent.hh"
#include "TagComponent.hh"

namespace volt::runtime {
  class Scene;

  using EID = entt::entity;
  using ECS_t = entt::registry;

  class Entity {
    EID m_id;
    Scene *m_scene;
  public:
    Entity(EID id, Scene *scene);
    inline const std::string &GetName(void)          { return GetComponent<TagComponent>().tag; }
    inline core::SnowflakeID::value_type GetID(void) { return static_cast<core::SnowflakeID::value_type>(GetComponent<IDComponent>().id); }
    template <IComponent_t T>
    bool HasComponent(void) const;
    template <IComponent_t T, typename... Args>
    T &AddComponent(Args &&... args);
    template <IComponent_t T>
    void RemoveComponent(void);
    template <IComponent_t T>
    T &GetComponent(void) const;
    template <IComponent_t T>
    T *TryGetComponent(void) const;
    inline operator EID(void) const noexcept { return m_id; }
  };

  class Scene {
    friend class Entity;
    std::string m_name;
    bool m_running;
    bool m_paused;
    ECS_t m_registry;
    b2WorldId m_worldID;
    std::unordered_map<core::SnowflakeID::value_type, EID> m_ids;
  public:
    Scene(const std::string &name);
    Scene(const Scene &) = delete;
    Scene(Scene &&) = delete;
    Scene &operator=(const Scene &) = delete;
    Scene &operator=(Scene &&) = delete;
    ~Scene(void);
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
    std::optional<Entity> FindEntityByID(core::SnowflakeID::value_type id);
    std::optional<Entity> FindEntityByName(const std::string &name);
    inline bool IsRunning(void) const noexcept { return m_running; }
    void Play(void) noexcept;
    void Pause(void) noexcept;
    void Stop(void) noexcept;
    inline const std::string &GetName(void) { return m_name; }
    inline void SetName(const std::string &name) { m_name = name; }
    inline b2WorldId GetPhysicsWorld(void) { return m_worldID; }
  };

  template <IComponent_t T>
  inline bool Entity::HasComponent(void) const {
    return m_scene->m_registry.any_of<T>(m_id);
  }

  template <IComponent_t T, typename... Args>
  inline T &Entity::AddComponent(Args &&... args) {
    assert(not HasComponent<T>());
    return m_scene->m_registry.emplace<T>(m_id, std::forward<Args>(args)...);
  }

  template <IComponent_t T>
  inline void Entity::RemoveComponent(void) {
    assert(HasComponent<T>());
    m_scene->m_registry.remove<T>(m_id);
  }

  template <IComponent_t T>
  inline T &Entity::GetComponent(void) const {
    assert(HasComponent<T>());
    return m_scene->m_registry.get<T>(m_id);
  }

  template <IComponent_t T>
  inline T *Entity::TryGetComponent(void) const {
    if (not HasComponent<T>()) return nullptr;
    return &GetComponent<T>();
  }
}
