struct TurningAround : volt::runtime::IBehaviour {
  int speed = 100;
  float angularSpeed = 45;

  void Update(volt::runtime::Entity &e) final {
    auto &t = e.GetComponent<volt::runtime::TransformComponent>();
    t.rotation += angularSpeed * volt::core::GetDeltaTime();
    t.position += (volt::core::Vector2<>::down().Rotate(t.rotation) * speed) * volt::core::GetDeltaTime();
  }
};
