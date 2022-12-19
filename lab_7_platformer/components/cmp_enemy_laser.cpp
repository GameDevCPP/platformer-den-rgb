#include "cmp_enemy_laser.h"
#include "cmp_bullet.h"
#include "cmp_hurt_player.h"
#include "engine.h"
#include "Pathfinding.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <cmath>

using namespace std;
using namespace sf;
Pathfinding pathfinder;
void EnemyLaserComponent::update(double dt) {
    _firetime -= dt;
    if (_firetime <= 0.f) {
        fire();
        _firetime = 1.f;
    }
}

void EnemyLaserComponent::fire() const {
    // Find the player Entity
    auto player = _parent->scene->ents.find("player")[0];
    auto player2 = _parent->scene->ents.find("player2")[0];

    // Create the bullet Entity
    auto bullet = _parent->scene->makeEntity();
    bullet->setPosition(_parent->getPosition());
    bullet->addComponent<HurtComponent>();
    bullet->addComponent<BulletComponent>();
    auto s = bullet->addComponent<ShapeComponent>();

    // Set the shape of the bullet to a circle
    s->setShape<sf::RectangleShape>(Vector2f(4.f, 40.f));
    s->getShape().setFillColor(Color::Red);
    s->getShape().setOrigin(Vector2f(2.f, 20.f));
    auto p = bullet->addComponent<PhysicsComponent>(true, Vector2f(8.f, 8.f));
    p->setRestitution(.4f);
    p->setFriction(.005f);

    // Use the A* pathfinding algorithm to find a path to the player
    auto path = pathfinder.aStar(_parent->getPosition(), player->getPosition());

    if (!path.empty()) {
        // Get the target point from the path
        auto target = path.back();

        // Calculate the angle between the turret and the target point
        auto angle = std::atan2(target.y - _parent->getPosition().y, target.x - _parent->getPosition().x);
        angle = angle * 180 / M_PI;

        // Set the rotation of the bullet to the angle
        bullet->setRotation(angle);

        // Set the velocity of the bullet to a value in the direction of the angle
        p->setVelocity(sf::rotate(Vector2f(0, 15.f), -angle));
    }

    auto path2 = pathfinder.aStar(_parent->getPosition(), player2->getPosition());

    if (!path2.empty()) {
        // Get the target point from the path
        auto target = path2.back();

        // Calculate the angle between the turret and the target point
        auto angle = std::atan2(target.y - _parent->getPosition().y, target.x - _parent->getPosition().x);
        angle = angle * 180 / M_PI;

        // Set the rotation of the bullet to the angle
        bullet->setRotation(angle);

        // Set the velocity of the bullet to a value in the direction of the angle
        p->setVelocity(sf::rotate(Vector2f(0, 15.f), -angle));
    }
}

EnemyLaserComponent::EnemyLaserComponent(Entity* p)
        : Component(p), _firetime(2.f) {}



