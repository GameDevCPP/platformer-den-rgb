#pragma once
#include "cmp_physics.h"
#include <ecm.h>

class HurtComponent : public Component {
protected:
  void fire() const;
  std::weak_ptr<Entity> _player1;
  std::weak_ptr<Entity> _player2;

public:
  void update(double dt) override;
  void render() override {}
  explicit HurtComponent(Entity* p);
  HurtComponent() = delete;
};
