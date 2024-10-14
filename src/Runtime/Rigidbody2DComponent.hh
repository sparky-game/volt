#pragma once

#include <box2d/box2d.h>
#include "IComponent.hh"
#include "../Core/Vector2.hh"

namespace volt::runtime {
  enum class Rigidbody2DType {
    Static = b2_staticBody,
    Kinematic = b2_kinematicBody,
    Dynamic = b2_dynamicBody
  };

  struct Rigidbody2DComponent : public IComponent {
    static inline auto cmp_name { "Rigidbody2D" };
    Rigidbody2DType type { Rigidbody2DType::Static };
    bool fixedRotation { false };
    float gravityScale { 1 };
    core::Vector2<float> linearVelocity { core::Vector2<>::zero() };
    Rigidbody2DComponent(void) = default;
    void Serialize(YAML::Emitter &out) final;
    bool Deserialize(YAML::Node &in) final;
    void Draw(void) final;
    inline b2BodyId GetBodyID(void) const { return m_bodyID; }
    inline void SetBodyID(b2BodyId id) { m_bodyID = id; }
    inline b2Vec2 GetExtent(void) const { return m_extent; }
    inline void SetExtent(const core::Vector2<float> &e) { m_extent = {e.X(), e.Y()}; }
  private:
    b2BodyId m_bodyID;
    b2Vec2 m_extent;
  };
}
