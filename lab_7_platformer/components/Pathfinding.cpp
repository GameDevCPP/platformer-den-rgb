#include "Pathfinding.h"
#include <queue>
#include <algorithm>
#include <cmath>
#include <unordered_map>

using namespace std;
using namespace sf;

struct Node {
    Vector2f position;
    float gScore;
    float fScore;
    Vector2f cameFrom;
};

bool operator<(const Node& a, const Node& b) {
    return a.fScore > b.fScore;
}

std::vector<sf::Vector2f> Pathfinding::aStar(sf::Vector2f start, sf::Vector2f end) {
    // If the start and end points are the same, return an empty path
    if (start == end) {
        return {};
    }

    // Initialize the open and closed sets
    priority_queue<Node> openSet;
    vector<Vector2f> closedSet;

    // Add the start node to the open set
    Node startNode = { start, 0.f, manhattanDistance(start, end), { 0, 0 } };
    openSet.push(startNode);

    // Keep track of the current node
    Vector2f current;

    // Mapping from positions to nodes in the open set
    unordered_map<int, Node> openSetMap;
    openSetMap[hashPosition(start)] = startNode;

    // Set a maximum number of iterations to prevent infinite loops
    int maxIterations = 1000;
    int numIterations = 0;

    while (!openSet.empty() && numIterations < maxIterations) {
        // Find the node in the open set with the lowest f-score
        current = openSet.top().position;
        openSet.pop();

        // If the current node is the end node, construct and return the path
        if (current == end) {
            vector<Vector2f> path;
            path.push_back(current);
            Vector2f parent = current;
            while (parent != start) {
                Node node = openSetMap[hashPosition(parent)];
                parent = node.cameFrom;
                path.push_back(parent);
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        // Add the current node to the closed set
        closedSet.push_back(current);

        // Iterate over the neighbors of the current node
        for (auto neighbor : getAdjacentNeighbors(current)) {
            // If the neighbor is already in the closed set, skip it
            if (std::find(closedSet.begin(), closedSet.end(), neighbor) != closedSet.end()) {
                continue;
            }

            // Calculate the tentative g-score for the neighbor
            float tentativeGScore = openSetMap[hashPosition(current)].gScore + euclideanDistance(current, neighbor);

            // If the neighbor is not in the open set, or if the tentative g-score is lower than the current g-score, update the g-score and f-score for the neighbor and add it to the open set
            if (openSetMap.find(hashPosition(neighbor)) == openSetMap.end() || tentativeGScore < openSetMap[hashPosition(neighbor)].gScore) {
                // element is not present in the map, or tentative g-score is lower than the current g-score
                Node updatedNode = { neighbor, tentativeGScore, tentativeGScore + manhattanDistance(neighbor, end), current };
                openSet.push(updatedNode);
                openSetMap[hashPosition(neighbor)] = updatedNode;
            }
        }

        // Increment the iteration counter
        numIterations++;
    }

    // If no path was found, return an empty path
    return {};

}



float Pathfinding::manhattanDistance(sf::Vector2f a, sf::Vector2f b) {
    // Calculate the Manhattan distance between the two points in terms of grid cells
    return abs(a.x - b.x) / 40.f + abs(a.y - b.y) / 40.f;
}

float Pathfinding::euclideanDistance(sf::Vector2f a, sf::Vector2f b) {
    // Calculate the Euclidean distance between the two points in terms of grid cells
    float dx = (a.x - b.x) / 40.f;
    float dy = (a.y - b.y) / 40.f;
    return sqrt(dx*dx + dy*dy);
}

std::vector<sf::Vector2f> Pathfinding::getAdjacentNeighbors(sf::Vector2f node) {
    std::vector<sf::Vector2f> neighbors;
    neighbors.push_back(sf::Vector2f(node.x - 1, node.y));
    neighbors.push_back(sf::Vector2f(node.x + 1, node.y));
    neighbors.push_back(sf::Vector2f(node.x, node.y - 1));
    neighbors.push_back(sf::Vector2f(node.x, node.y + 1));
    return neighbors;
}

int Pathfinding::hashPosition(sf::Vector2f position) {
    // Hash the position by converting its coordinates to integers and combining them into a single integer
    int x = static_cast<int>(position.x);
    int y = static_cast<int>(position.y);
    return x * 1000 + y;
}
