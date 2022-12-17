//LevelSystem.cpp
#include "LevelSystem.h"
#include <fstream>

using namespace std;
using namespace sf;

std::unique_ptr<LevelSystem::Tile[]> LevelSystem::_tiles;
size_t LevelSystem::_width;
size_t LevelSystem::_height;

float LevelSystem::_tileSize(100.f);
Vector2f LevelSystem::_offset(0.0f, 30.0f);
vector<std::unique_ptr<sf::RectangleShape>> LevelSystem::_sprites;

std::map<LevelSystem::Tile, sf::Color> LevelSystem::_colours = {
        {LevelSystem::WALL, sf::Color::Black},
        {LevelSystem::END, sf::Color::Green},
        {LevelSystem::PLATFORM, sf::Color::Blue}
        // Add other mappings as needed
};

void LevelSystem::loadLevelFile(const std::string& path, map<Tile, Color> colours, float tileSize) {

    _tileSize = tileSize;
    _colours = colours;

    // Load the image file into a sf::Image object
    sf::Image levelImage;
    if (!levelImage.loadFromFile(path)) {
        throw string("Couldn't open level image file: ") + path;
    }

    // Get the width and height of the image
    _width = levelImage.getSize().x;
    _height = levelImage.getSize().y;

    // Create a new Tile array to store the level data
    _tiles = std::make_unique<Tile[]>(_width * _height);

    // Iterate through each pixel in the image and determine the corresponding Tile based on its color
    for (size_t y = 0; y < _height; ++y) {
        for (size_t x = 0; x < _width; ++x) {
            sf::Color pixelColor = levelImage.getPixel(Vector2u(x, y));
            if (pixelColor == _colours[WALL]) {
                _tiles[y * _width + x] = WALL;
            } else if (pixelColor == _colours[END]) {
                _tiles[y * _width + x] = END;
            } else if (pixelColor == _colours[PLATFORM]) {
                _tiles[y * _width + x] = PLATFORM;
            } else {
                _tiles[y * _width + x] = EMPTY;
            }
        }
    }

    cout << "Level " << path << " Loaded. " << _width << "x" << _height << std::endl;
    buildSprites();
}

void LevelSystem::unload() {
    _tiles.reset();
    _sprites.clear();
    _width = 0;
    _height = 0;
}

void LevelSystem::render(sf::RenderWindow& window) {
    for (const auto& sprite : _sprites) {
        window.draw(*sprite);
    }
}

LevelSystem::Tile LevelSystem::getTile(sf::Vector2ul p) {
    if (p.x > _width || p.y > _height) {
        return TILES::EMPTY;
    }
    return _tiles[p.y * _width + p.x];
}

LevelSystem::Tile LevelSystem::getTileAt(sf::Vector2f p) {
    p -= _offset;
    p /= _tileSize;
    return getTile({(unsigned int)p.x, (unsigned int)p.y});
}

bool LevelSystem::isOnGrid(sf::Vector2f p) {
    p -= _offset;
    p /= _tileSize;
    auto x = (unsigned int)p.x;
    auto y = (unsigned int)p.y;
    return (x < _width && y < _height);
}

size_t LevelSystem::getWidth() {
    return _width;
}

size_t LevelSystem::getHeight() {
    return _height;
}

sf::Vector2f LevelSystem::getTilePosition(sf::Vector2ul p) {
    return Vector2f(p.x * _tileSize, p.y * _tileSize) + _offset;
}

vector<sf::Vector2ul> LevelSystem::findTiles(Tile t) {
    vector<sf::Vector2ul> found;
    for (size_t y = 0; y < _height; ++y) {
        for (size_t x = 0; x < _width; ++x) {
            if (getTile({x, y}) == t) {
                found.push_back({x, y});
            }
        }
    }
    return found;
}

void LevelSystem::setOffset(const Vector2f& offset) {
    _offset = offset;
}

const Vector2f& LevelSystem::getOffset() {
    return _offset;
}

float LevelSystem::getTileSize() {
    return _tileSize;
}

void LevelSystem::buildSprites(bool optimise) {
    _sprites.clear();

    struct tp {
        sf::Vector2f p;
        sf::Vector2f s;
        sf::Color c;
    };
    vector<tp> tps;
    const auto tls = Vector2f(_tileSize, _tileSize);
    for (size_t y = 0; y < _height; ++y) {
        for (size_t x = 0; x < _width; ++x) {
            Tile t = getTile({x, y});
            if (t == EMPTY) {
                continue;
            }
            tps.push_back({getTilePosition({x, y}), tls, _colours[t]});
        }
    }

    const auto nonempty = tps.size();
    if (optimise) {
        for (size_t i = 0; i < nonempty; ++i) {
            auto& tpi = tps[i];
            if (tpi.c.a == 0) {
                continue;
            }
            bool added = false;
            for (size_t j = i + 1; j < nonempty; ++j) {
                auto& tpj = tps[j];
                if (tpj.c.a == 0) {
                    continue;
                }
                if (tpi.p == tpj.p && tpi.s == tpj.s && tpi.c == tpj.c) {
                    tpj.c.a = 0;
                    added = true;
                }
            }
            if (!added) {
                tpi.c.a = 0;
            }
        }
    }

    for (const auto& tp : tps) {
        auto sprite = make_unique<RectangleShape>();
        sprite->setPosition(tp.p);
        sprite->setSize(tp.s);
        sprite->setFillColor(tp.c);
        _sprites.push_back(move(sprite));
    }
}