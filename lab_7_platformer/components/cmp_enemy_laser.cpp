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

#include <vector>
#include <utility>
#include <set>
#include <cmath>
#include <map>

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

// Function to calculate the heuristic cost of moving from one position to another
double heuristic(sf::Vector2f pos1, sf::Vector2f pos2)
{
    return std::sqrt((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y));
}

//std::vector<sf::Vector2f> findPathToPlayer(sf::Vector2f start, sf::Vector2f end, int mapWidth, int mapHeight)
//{
//    // Set up data structures for the A* search
//    std::set<std::pair<double, sf::Vector2f>> openSet;
//    std::set<sf::Vector2f> closedSet;
//    std::map<sf::Vector2f, sf::Vector2f> cameFrom;
//    std::map<sf::Vector2f, double> gScore;
//    std::map<sf::Vector2f, double> fScore;
//
//    // Add the start position to the open set and initialize its g and f scores
//    openSet.insert(std::make_pair(0, start));
//    gScore[start] = 0;
//    fScore[start] = heuristic(start, end);
//
//    // Loop until the open set is empty or the end position is found
//    while (!openSet.empty())
//    {
//        // Find the position in the open set with the lowest f score
//        sf::Vector2f current = openSet.begin()->second;
//        if (current == end)
//        {
//            // If the end position is found, construct and return the path
//            std::vector<sf::Vector2f> path;
//            while (current != start)
//            {
//                path.push_back(current);
//                current = cameFrom[current];
//            }
//            path.push_back(start);
//            std::reverse(path.begin(), path.end());
//            return path;
//        }
//
//        // Remove the current position from the open set and add it to the closed set
//        openSet.erase(openSet.begin());
//        closedSet.insert(current);
//
//        // Consider each neighbor of the current position
//        for (int i = 0; i < 4; i++)
//        {
//            sf::Vector2f neighbor(current.x + dx[i], current.y + dy[i]);
//
//            // Skip this neighbor if it is outside the map or has already been considered
//            if (neighbor.x < 0 || neighbor.x >= mapWidth || neighbor.y < 0 || neighbor.y >= mapHeight || closedSet.count(neighbor))
//                continue;
//
//            // Calculate the tentative g score for the neighbor
//            double tentativeGScore = gScore[current] + 1; // Assume a cost of 1 to
//
//            if (!openSet.count(neighbor) || tentativeGScore < gScore[neighbor])
//            {
//                cameFrom[neighbor] = current;
//                gScore[neighbor] = tentativeGScore;
//                fScore[neighbor] = gScore[neighbor] + heuristic(neighbor, end);
//                openSet.insert(std::make_pair(fScore[neighbor], neighbor));
//            }
//        }
//    }
//
//// If the open set is empty, no path to the end position was found
//    return std::vector<sf::Vector2f>();
//
//}
EnemyLaserComponent::EnemyLaserComponent(Entity* p)
        : Component(p), _firetime(2.f) {}



