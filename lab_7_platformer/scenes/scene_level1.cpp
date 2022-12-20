//scene_level1.cpp
#include "scene_level1.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_sprite.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;
static shared_ptr<Entity> player2;
int endCounter1 = 0;
int endCounter2 = 0;
void Level1Scene::Load() {
    cout << " Scene 1 Load" << endl;

    LevelSystem::loadLevelFile("res/Level1.png", LevelSystem::_colours, 40.0f);
    {
        makePlayer(player);
        makePlayer(player2);
    }


    // Find all WALL tiles and add physics colliders to them

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

    //Simulate long loading times
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    cout << " Scene 1 Load Done" << endl;

    setLoaded(true);
}

void Level1Scene::UnLoad() {
    cout << "Scene 1 Unload" << endl;
    player.reset();
    player2.reset();
    LevelSystem::unload();
    Scene::UnLoad();
}

void Level1Scene::Update(const double& dt) {

    // Check if player is on an END tile and change to the next scene if they are
    if (LevelSystem::getTileAt(player->getPosition()) == LevelSystem::END ) {
        endCounter1=1;
    }else{
        endCounter1=0;
    }

    if (LevelSystem::getTileAt(player2->getPosition()) == LevelSystem::END ) {
        endCounter2=1;
    }else{
        endCounter2=0;
    }

    if (endCounter1 + endCounter2 >=2) {
        Engine::ChangeScene((Scene*)&level2);
    }
    Scene::Update(dt);
}

void Level1Scene::makePlayer(shared_ptr<Entity> &p){
    if (p == player) {
        p= makeEntity();
        p->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
        p->addTag("player");
    } else if (p == player2){
        p= makeEntity();
        p->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[1]));
        p->addTag("player2");
    }
    auto s = p->addComponent<ShapeComponent>();
    s->setShape<sf::RectangleShape>(Vector2f(20.f, 20.f));
    s->getShape().setFillColor(Color::Magenta);
    s->getShape().setOrigin(Vector2f(10.f, 10.f));
    p->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 20.f));
}

void Level1Scene::Render() {
    LevelSystem::render(Engine::GetWindow());
    Scene::Render();
}