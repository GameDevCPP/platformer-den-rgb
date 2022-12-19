#pragma once

#include "engine.h"


class Level3Scene : public Scene {
public:
  void Load() override;

  void UnLoad() override;

  void Update(const double& dt) override;

  void Render() override;

  void makePlayer(std::shared_ptr<Entity> &p);
};
