#include "scene_level2.h"
#include "../components/cmp_enemy_ai.h"
#include "../components/cmp_enemy_turret.h"
#include "../components/cmp_enemy_laser.h"
#include "../components/cmp_hurt_player.h"
#include "../components/cmp_physics.h"
#include "../components/cmp_player_physics.h"
#include "../game.h"
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

    LevelSystem::loadLevelFile("res/test3.png", LevelSystem::_colours, 40.0f);
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

            auto s = laser->addComponent<ShapeComponent>();
            s->setShape<sf::RectangleShape>(Vector2f(6.f, 40.f));
            s->getShape().setFillColor(Color::White);
            s->getShape().setOrigin(Vector2f(3.f, 10.f));

            auto t = laser->addComponent<ShapeComponent>();
            t->setShape<sf::CircleShape>(5.f);
            t->getShape().setFillColor(Color::Red);
            t->getShape().setOrigin(Vector2f(5.f, 15.f));

            auto b = laser->addComponent<ShapeComponent>();
            b->setShape<sf::CircleShape>(10.f, 3);
            b->getShape().setFillColor(Color::Red);
            b->getShape().setOrigin(Vector2f(10.f, 0.f));

            laser->addComponent<PhysicsComponent>(false, Vector2f(6.f, 40.f));
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

            auto s = turret->addComponent<ShapeComponent>();
            s->setShape<sf::CircleShape>(20.f, 4);
            s->getShape().setFillColor(Color::Yellow);
            s->getShape().setOrigin(Vector2f(20.f, 20.f));

            turret->addComponent<EnemyTurretComponent>();
            turret->addComponent<HurtComponent>();
        }


    }

    {
        int numEnemyTiles = ls::findTiles(ls::ENEMY).size();
        for (int i = 0; i < numEnemyTiles; i++) {
            auto enemy = makeEntity();

            // Set the position of the enemy to the position of the ENEMY[i] tile
            // plus an offset of (0, 24)
            enemy->setPosition(ls::getTilePosition(ls::findTiles(ls::ENEMY)[i]) +
                               Vector2f(0, 24));
            enemy->addComponent<EnemyAIComponent>();
            enemy->addComponent<HurtComponent>();
            enemy->addComponent<PhysicsComponent>(false, Vector2f(16.f, 16.f));
            auto e = enemy->addComponent<ShapeComponent>();
            e->setShape<sf::CircleShape>(16.f);
            e->getShape().setFillColor(Color::Red);
            e->getShape().setOrigin(Vector2f(16.f, 16.f));
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
            auto wall = e->addComponent<ShapeComponent>();
            wall->setShape<sf::RectangleShape>(Vector2f(40.f, 40.f));
            wall->getShape().setFillColor(Color::White);
            wall->getShape().setOrigin(Vector2f(20.f, 20.f));
        }

        auto platformTiles = LevelSystem::findTiles(LevelSystem::PLATFORM);
        for (auto w : platformTiles) {
            auto pos = LevelSystem::getTilePosition(w);
            pos += Vector2f(20.f, 5.f); //offset to center
            auto e = makeEntity();
            e->setPosition(pos);
            e->addComponent<PhysicsComponent>(false, Vector2f(40.f, 20.f));
            auto wall = e->addComponent<ShapeComponent>();
            wall->setShape<sf::RectangleShape>(Vector2f(40.f, 20.f));
            wall->getShape().setFillColor(Color::Cyan);
            wall->getShape().setOrigin(Vector2f(20.f, 5.f));
        }

        auto endTiles = LevelSystem::findTiles(LevelSystem::END);
        for (auto w : endTiles) {
            auto pos = LevelSystem::getTilePosition(w);
            pos += Vector2f(20.f, 20.f); //offset to center
            auto e = makeEntity();
            e->setPosition(pos);
            e->addComponent<PhysicsComponent>(false, Vector2f(40.f, 10.f));
            auto end = e->addComponent<ShapeComponent>();
            end->setShape<sf::RectangleShape>(Vector2f(40.f, 10.f));
            end->getShape().setFillColor(Color::Green);
            end->getShape().setOrigin(Vector2f(20.f, 5.f));
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
        Engine::ChangeScene((Scene*)&level1);
    }

    if (!player->isAlive()) {
        makePlayer(player);
    }
    if (!player2->isAlive()){
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
    auto s = p->addComponent<ShapeComponent>();
    s->setShape<sf::RectangleShape>(Vector2f(20.f, 20.f));
    s->getShape().setFillColor(Color::Magenta);
    s->getShape().setOrigin(Vector2f(10.f, 10.f));
    p->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 20.f));
}



void Level3Scene::Render() {
    ls::render(Engine::GetWindow());
    Scene::Render();
}
