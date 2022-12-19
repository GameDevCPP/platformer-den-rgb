#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <SFML/System/Vector2.hpp>
#include <vector>

class Pathfinding {
public:
    std::vector<sf::Vector2f> aStar(sf::Vector2f start, sf::Vector2f end);

    float distance(sf::Vector2f a, sf::Vector2f b);

    std::vector<sf::Vector2f> getNeighbors(sf::Vector2f node);

    float manhattanDistance(sf::Vector2f a, sf::Vector2f b);

    int hashPosition(sf::Vector2f position);

    std::vector<sf::Vector2f> getAdjacentNeighbors(sf::Vector2f node);

    float euclideanDistance(sf::Vector2f a, sf::Vector2f b);
};

#endif // PATHFINDING_H
