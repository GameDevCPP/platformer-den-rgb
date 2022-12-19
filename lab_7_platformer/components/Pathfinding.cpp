#include "Pathfinding.h"
#include <queue>
#include <vector>
#include <algorithm>
#include <cmath>

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
    // Initialize the open and closed sets
    priority_queue<Node> openSet;
    vector<Vector2f> closedSet;

    // Add the start node to the open set
    Node startNode = { start, 0.f, distance(start, end), { 0, 0 } };
    openSet.push(startNode);

    // Keep track of the current node
    Vector2f current;

    while (!openSet.empty()) {
        // Find the node in the open set with the lowest f-score
        current = openSet.top().position;
        openSet.pop();

        // If the current node is the end node, construct and return the path
        if (current == end) {
            vector<Vector2f> path;
            path.push_back(current);
            Vector2f parent = current;
            while (parent != start) {
                Node node = openSet.top();
                while (node.position != parent) {
                    openSet.pop();
                    node = openSet.top();
                }
                parent = node.cameFrom;
                path.push_back(parent);
            }
            reverse(path.begin(), path.end());
            return path;
        }

        // Add the current node to the closed set
        closedSet.push_back(current);

        // Iterate over the neighbors of the current node
        for (auto neighbor : getNeighbors(current)) {
            // If the neighbor is already in the closed set, skip it
            if (std::find(closedSet.begin(), closedSet.end(), neighbor) != closedSet.end()) {
                continue;
            }

            // Calculate the tentative g-score for the neighbor
            float tentativeGScore = openSet.top().gScore + distance(current, neighbor);

            // If the neighbor is not in the open set, or if the tentative g-score is lower than the current g-score, update the g-score and f-score for the neighbor and add it to the open set
            bool found = false;
            Node node = openSet.top();
            while (!openSet.empty()) {
                if (node.position == neighbor) {
                    found = true;
                    if (tentativeGScore < node.gScore) {
                        Node updatedNode = { neighbor, tentativeGScore, tentativeGScore + distance(neighbor, end), current };
                        openSet.push(updatedNode);
                    }
                    break;
                }
                openSet.pop();
                node = openSet.top();
            }
            if (!found) {
                Node newNode = { neighbor, tentativeGScore, tentativeGScore + distance(neighbor, end), current };
                openSet.push(newNode);
            }
        }
    }

    // If no path was found, return an empty path
    return {};
}

float Pathfinding::distance(sf::Vector2f a, sf::Vector2f b) {
    // Calculate the Euclidean distance between the two points
    return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

std::vector<sf::Vector2f> Pathfinding::getNeighbors(sf::Vector2f node) {
    std::vector<sf::Vector2f> neighbors;
    neighbors.push_back(sf::Vector2f(node.x - 1, node.y));
    neighbors.push_back(sf::Vector2f(node.x + 1, node.y));
    neighbors.push_back(sf::Vector2f(node.x, node.y - 1));
    neighbors.push_back(sf::Vector2f(node.x, node.y + 1));
    return neighbors;
}
