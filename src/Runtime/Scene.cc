#include "Scene.hh"
#include <unordered_map>
#include "../Core/LogSystem.hh"
#include "TransformComponent.hh"
#include "Rigidbody2DComponent.hh"
#include "../Renderer/SpriteRendererComponent.hh"

namespace volt::runtime {
  static std::unordered_map<core::SnowflakeID::value_type, core::Vector2<float>> initial_positions;
  static std::unordered_map<core::SnowflakeID::value_type, float> initial_rotations;

  Entity::Entity(EID id, Scene *scene)
    : m_id{id}, m_scene{scene}
  {}

  Scene::Scene(const std::string &name)
    : m_name{name}, m_running{false}, m_paused{false}
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
    if (not m_paused) {
      b2WorldDef worldDef = b2DefaultWorldDef();
      worldDef.gravity = {0.0f, 9.81f};
      m_worldID = b2CreateWorld(&worldDef);
    }
    ForAll<TransformComponent, Rigidbody2DComponent, renderer::SpriteRendererComponent>([this](auto e, auto &t, auto &rb, auto &sr) {
      rb.SetExtent({t.scale * sr.sprite.width() * 0.5f, t.scale * sr.sprite.height() * 0.5f});
      b2BodyDef bodyDef { b2DefaultBodyDef() };
      bodyDef.type = static_cast<b2BodyType>(rb.type);
      bodyDef.gravityScale = rb.gravityScale;
      bodyDef.fixedRotation = rb.fixedRotation;
      bodyDef.position = {t.position.X(), t.position.Y()};
      bodyDef.rotation = b2MakeRot(t.rotation * DEG2RAD);
      rb.SetBodyID(b2CreateBody(m_worldID, &bodyDef));
      b2Polygon polygon { b2MakeBox(rb.GetExtent().x, rb.GetExtent().y) };
      b2ShapeDef shapeDef { b2DefaultShapeDef() };
      b2CreatePolygonShape(rb.GetBodyID(), &shapeDef, &polygon);
      // NOTE: Save initial position and rotation (if wasn't in paused state, to not overwrite actual initial values)
      if (not m_paused) {
        initial_positions[e.GetID()] = t.position;
        initial_rotations[e.GetID()] = t.rotation;
      }
    });
    if (m_paused) m_paused = false;
  }

  void Scene::Pause(void) noexcept {
    if (m_running) m_running = false;
    if (not m_paused) m_paused = true;
  }

  void Scene::Stop(void) noexcept {
    if (m_running) m_running = false;
    if (m_paused) m_paused = false;
    for (auto &[id, pos] : initial_positions) {
      auto &t { FindEntityByID(id)->GetComponent<TransformComponent>() };
      t.position = pos;
      t.rotation = initial_rotations[id];
    }
    b2DestroyWorld(m_worldID);
  }
}
