//
// Created by denism on 12/19/22.
//

#ifndef GAMES_ENGINEERING_CMP_ENEMY_LASER_H
#define GAMES_ENGINEERING_CMP_ENEMY_LASER_H


#include <ecm.h>
#include <SFML/Graphics/CircleShape.hpp>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "../../lib_ecm/ecm.h"

class EnemyLaserComponent : public Component {
protected:
    void fire() const;
    float _firetime;
public:
    void update(double dt) override;
    explicit EnemyLaserComponent(Entity* p);
    void render() override {}
    EnemyLaserComponent() = delete;
};
// Define new function that uses A* pathfinding algorithm to locate player and output laser towards player
std::vector<sf::Vector2f> findPathToPlayer(sf::Vector2f start, sf::Vector2f end, int mapWidth, int mapHeight);

#endif //GAMES_ENGINEERING_CMP_ENEMY_LASER_H



