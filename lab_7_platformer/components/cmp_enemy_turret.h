#pragma once
#include "cmp_physics.h"
#include <ecm.h>

class EnemyTurretComponent : public Component {
protected:

    void fire();
    float _firetime;
    float _timer;
private:
//    std::shared_ptr<Entity> bullet;
    std::vector<std::shared_ptr<Entity>> _availableBullets;
public:
    std::shared_ptr<Entity> getBullet();
    void returnBullet(std::shared_ptr<Entity> bullet);
    void update(double dt) override;
    void render() override {}
    explicit EnemyTurretComponent(Entity* p);
    EnemyTurretComponent() = delete;
};