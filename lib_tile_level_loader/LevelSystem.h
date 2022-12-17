//LevelSystem.h
#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include "maths.h"

#define ls LevelSystem

class LevelSystem {
public:

    enum TILES {
        EMPTY = ' ',
        START = 's',
        END = 'e',
        WALL = 'w',
        PLATFORM = 'p',
        ENEMY = 'n',
        WAYPOINT = '+'
    };
    typedef unsigned char Tile;
    static void loadLevelFile(const std::string&, std::map<Tile, sf::Color>, float tileSize = 100.0f);
    static void unload();
    static void render(sf::RenderWindow& window);


    static Tile getTile(sf::Vector2ul);

    static Tile getTileAt(sf::Vector2f);

    static bool isOnGrid(sf::Vector2f);

    static size_t getWidth();

    static size_t getHeight();

    static sf::Vector2f getTilePosition(sf::Vector2ul);

    static std::vector<sf::Vector2ul> findTiles(Tile);

    static void setOffset(const sf::Vector2f& _offset);

    static const sf::Vector2f& getOffset();

    static float getTileSize();

    static std::map<Tile, sf::Color> _colours;

protected:
    static std::unique_ptr<Tile[]> _tiles;
    static size_t _width;
    static size_t _height;
    static sf::Vector2f _offset;

    static std::vector<std::unique_ptr<sf::RectangleShape>> _sprites;

    static void buildSprites(bool optimise = true);

    static float _tileSize; // for rendering

private:
    LevelSystem() = delete;

    ~LevelSystem() = delete;
};