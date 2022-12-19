#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <SFML/System/Vector2.hpp>
#include <vector>

class Pathfinding {
public:
    std::vector<sf::Vector2f> aStar(sf::Vector2f start, sf::Vector2f end);

    float distance(sf::Vector2f a, sf::Vector2f b);

    std::vector<sf::Vector2f> getNeighbors(sf::Vector2f node);
};

#endif // PATHFINDING_H
