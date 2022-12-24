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
    _timer -=dt;
    if (_firetime <= 0.f) {
        fire();
        _firetime = 2.f;
    }
    static float angle = 0.f;
    angle += 1.f * dt;

    _parent->setRotation(180.f + sin(angle) * 45.f);

//    if(_timer<= 0.f) {
//        returnBullet(bullet);
//        bullet->addComponent<BulletComponent>();
//        _timer=2.f;
//    }

}

void EnemyTurretComponent::fire() {
// Check if there is at least one available bullet
    if (!_availableBullets.empty()) {
// Retrieve a bullet object from the object pool
        auto bullet = getBullet();
// Set the position of the bullet object
        bullet->setPosition(_parent->getPosition());
//        bullet->addComponent<HurtComponent>();
        // Add the PhysicsComponent to the bullet object and set its properties
        auto p = bullet->addComponent<PhysicsComponent>(true, Vector2f(8.f, 8.f));
        p->setRestitution(.4f);
        p->setFriction(.005f);
        p->impulse(sf::rotate(Vector2f(0, 15.f), -_parent->getRotation()));
        returnBullet(bullet);

    }

}

EnemyTurretComponent::EnemyTurretComponent(Entity* p)
        : Component(p), _firetime(2.f), _timer(3.f) {

    auto bullet = _parent->scene->makeEntity();

    // Add the HurtComponent and BulletComponent to the bullet object
    bullet->addComponent<HurtComponent>();
//        bullet->addComponent<BulletComponent>();

    // Add the SpriteComponent to the bullet object and set its texture
    auto sprite = bullet->addComponent<SpriteComponent>();
    auto texture = std::make_shared<sf::Texture>();
    if (!texture->loadFromFile("res/sprites/bullets.png")) {
        // Error loading the texture
        std::cout << "Error loading player texture" << std::endl;
        exit(1);
    }
    sprite->setTexture(texture);
    sprite->getSprite().setOrigin(Vector2f(8.f, 8.f));

    // Add the bullet object to the list of available bullet objects
    _availableBullets.push_back(bullet);

}

// Function to retrieve a bullet object from the object pool
std::shared_ptr<Entity> EnemyTurretComponent::getBullet() {
// Retrieve the first available bullet object
    auto  bullet = _availableBullets.back();
// Remove the bullet object from the list of available objects
    _availableBullets.pop_back();
// Return the bullet object
    return bullet;
}

// Function to return a bullet object to the object pool
void EnemyTurretComponent::returnBullet(std::shared_ptr<Entity> bullet) {

// Add the bullet object to the list of available bullet objects
    _availableBullets.push_back(bullet);
}