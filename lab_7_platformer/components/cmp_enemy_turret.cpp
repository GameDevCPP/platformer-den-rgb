#include "cmp_enemy_turret.h"
#include "cmp_bullet.h"
#include "cmp_hurt_player.h"
#include "engine.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

void EnemyTurretComponent::update(double dt) {
    _firetime -= dt;
    if (_firetime <= 0.f) {
        fire();
        _firetime = 1.f;
    }
    static float angle = 0.f;
    angle += 1.f * dt;

    _parent->setRotation(180.f + sin(angle) * 45.f);
}

void EnemyTurretComponent::fire() const {
    auto bullet = _parent->scene->makeEntity();
    bullet->setPosition(_parent->getPosition());
    bullet->addComponent<HurtComponent>();
    bullet->addComponent<BulletComponent>();

    auto p = bullet->addComponent<PhysicsComponent>(true, Vector2f(8.f, 8.f));
    p->setRestitution(.4f);
    p->setFriction(.005f);
    p->impulse(sf::rotate(Vector2f(0, 15.f), -_parent->getRotation()));
    auto sprite = bullet->addComponent<SpriteComponent>();
    auto texture = make_shared<sf::Texture>();
    if (!texture->loadFromFile("res/sprites/bullets.png")) {
        // Error loading the texture
        std::cout << "Error loading player texture" << std::endl;
        exit(1);
    }

// Set the texture on the sprite
    sprite->setTexture(texture);
    sprite->getSprite().setOrigin(Vector2f(20.f,20.f));
}

EnemyTurretComponent::EnemyTurretComponent(Entity* p)
        : Component(p), _firetime(2.f) {}
