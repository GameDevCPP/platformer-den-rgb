#include "scene_level2.h"
#include "../components/cmp_enemy_ai.h"
#include "../components/cmp_enemy_turret.h"
#include "../components/cmp_enemy_laser.h"
#include "../components/cmp_hurt_player.h"
#include "../components/cmp_physics.h"
#include "../components/cmp_player_physics.h"
#include "../game.h"
#include "../components/SoundEffects.h"
#include <LevelSystem.h>
#include <iostream>

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;
static shared_ptr<Entity> player2;
int l3endCounter1 = 0;
int l3endCounter2 = 0;
void Level3Scene::Load() {
    cout << "Scene 2 Load" << endl;

    LevelSystem::loadLevelFile("res/test31.png", LevelSystem::_colours, 40.0f);
    auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
    ls::setOffset(Vector2f(0, ho));


    // Create player
    {
        makePlayer(player);
        makePlayer(player2);
    }

    // Create Laser

    {
        int numLaserTiles = ls::findTiles(ls::LASER).size();
        for (int i = 0; i < numLaserTiles; i++) {
            auto laser = makeEntity();

            // Set the position of the enemy to the position of the ENEMY[i] tile
            // plus an offset of (20, 0)
            laser->setPosition(ls::getTilePosition(ls::findTiles(ls::LASER)[i]) +
                                Vector2f(0, 25));

            auto sprite = laser->addComponent<SpriteComponent>();
            auto texture = make_shared<sf::Texture>();
            if (!texture->loadFromFile("res/sprites/laser.png")) {
                // Error loading the texture
                std::cout << "Error loading player texture" << std::endl;
                exit(1);
            }

// Set the texture on the sprite
            sprite->setTexture(texture);
            sprite->getSprite().setOrigin(Vector2f(10.f,20.f));

            laser->addComponent<PhysicsComponent>(false, Vector2f(10.f, 20.f));
            laser->addComponent<EnemyLaserComponent>();
        }

    }


    // Create Turret
    {
        int numEnemyTiles = ls::findTiles(ls::ENEMY).size();
        for (int i = 0; i <numEnemyTiles; i++) {
            auto turret = makeEntity();

            // Set the position of the enemy to the position of the ENEMY[i] tile
            // plus an offset of (20, 0)
            turret->setPosition(ls::getTilePosition(ls::findTiles(ls::ENEMY)[i]) +
                                Vector2f(0, 25));

            auto sprite = turret->addComponent<SpriteComponent>();
            auto texture = make_shared<sf::Texture>();
            if (!texture->loadFromFile("res/sprites/turret.png")) {
                // Error loading the texture
                std::cout << "Error loading player texture" << std::endl;
                exit(1);
            }

// Set the texture on the sprite
            sprite->setTexture(texture);
            sprite->getSprite().setOrigin(Vector2f(20.f,20.f));
//            turret->addComponent<EnemyAIComponent>();
            turret->addComponent<EnemyTurretComponent>();
            turret->addComponent<HurtComponent>();
        }


    }

    // Add physics colliders to level tiles.
    {
        // *********************************
        auto wallTiles = LevelSystem::findTiles(LevelSystem::WALL);
        for (auto w : wallTiles) {
            auto pos = LevelSystem::getTilePosition(w);
            pos += Vector2f(20.f, 20.f); //offset to center
            auto e = makeEntity();
            e->setPosition(pos);
            e->addComponent<PhysicsComponent>(false, Vector2f(40.f, 40.f));
            auto sprite = e->addComponent<SpriteComponent>();
            auto texture = make_shared<sf::Texture>();
            if (!texture->loadFromFile("res/sprites/wall.png")) {
                // Error loading the texture
                std::cout << "Error loading player texture" << std::endl;
                exit(1);
            }

// Set the texture on the sprite
            sprite->setTexture(texture);
            sprite->getSprite().setOrigin(Vector2f(20.f,10.f));
        }

        auto platformTiles = LevelSystem::findTiles(LevelSystem::PLATFORM);
        for (auto w : platformTiles) {
            auto pos = LevelSystem::getTilePosition(w);
            pos += Vector2f(20.f, 5.f); //offset to center
            auto e = makeEntity();
            e->setPosition(pos);
            e->addComponent<PhysicsComponent>(false, Vector2f(40.f, 20.f));
            auto sprite = e->addComponent<SpriteComponent>();
            auto texture = make_shared<sf::Texture>();
            if (!texture->loadFromFile("res/sprites/platform.png")) {
                // Error loading the texture
                std::cout << "Error loading player texture" << std::endl;
                exit(1);
            }

// Set the texture on the sprite
            sprite->setTexture(texture);
            sprite->getSprite().setOrigin(Vector2f(20.f,10.f));
        }

        auto endTiles = LevelSystem::findTiles(LevelSystem::END);
        for (auto w : endTiles) {
            auto pos = LevelSystem::getTilePosition(w);
            pos += Vector2f(20.f, 20.f); //offset to center
            auto e = makeEntity();
            e->setPosition(pos);
            e->addComponent<PhysicsComponent>(false, Vector2f(40.f, 10.f));
            auto sprite = e->addComponent<SpriteComponent>();
            auto texture = make_shared<sf::Texture>();
            if (!texture->loadFromFile("res/sprites/end.png")) {
                // Error loading the texture
                std::cout << "Error loading player texture" << std::endl;
                exit(1);
            }

// Set the texture on the sprite
            sprite->setTexture(texture);
            sprite->getSprite().setOrigin(Vector2f(20.f,10.f));
        }
        // *********************************
    }

    cout << " Scene 2 Load Done" << endl;
    setLoaded(true);
}

void Level3Scene::UnLoad() {
    cout << "Scene 2 UnLoad" << endl;
    player.reset();
    player2.reset();
    ls::unload();
    Scene::UnLoad();
}

void Level3Scene::Update(const double& dt) {


    if (LevelSystem::getTileAt(player->getPosition()) == LevelSystem::END ) {
        l3endCounter1=1;
    }else{
        l3endCounter1=0;
    }

    if (LevelSystem::getTileAt(player2->getPosition()) == LevelSystem::END ) {
        l3endCounter2=1;
    }else{
        l3endCounter2=0;
    }

    if (l3endCounter1 + l3endCounter2 >=2) {
        Engine::ChangeScene((Scene*)&menu);
    }

    if (!player->isAlive()) {
        SoundEffects::play("res/audio/die.wav");
        makePlayer(player);
    }
    if (!player2->isAlive()){
        SoundEffects::play("res/audio/die.wav");
        makePlayer(player2);
    }

    Scene::Update(dt);
}

void Level3Scene::makePlayer(shared_ptr<Entity> &p){
    if (p == player) {
        p= makeEntity();
        p->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
        p->addTag("player");
    } else if (p == player2){
        p= makeEntity();
        p->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[1]));
        p->addTag("player2");
    }

    // Load the sprite for the player
    auto sprite = p->addComponent<SpriteComponent>();
    auto texture = make_shared<sf::Texture>();
    if (!texture->loadFromFile("res/sprites/player.png")) {
        // Error loading the texture
        std::cout << "Error loading player texture" << std::endl;
        exit(1);
    }

// Set the texture on the sprite
    sprite->setTexture(texture);
    sprite->getSprite().setScale(Vector2f (1.0f/2, 1.0f/2));
    sprite->getSprite().setOrigin(Vector2f(15.f,15.f));
    p->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 20.f));
}





void Level3Scene::Render() {
    ls::render(Engine::GetWindow());
    Scene::Render();
}
