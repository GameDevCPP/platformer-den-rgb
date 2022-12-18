#include "cmp_hurt_player.h"
#include <engine.h>

using namespace std;
using namespace sf;

void HurtComponent::update(double dt) {
// Check if player1 is within range and set it for deletion if it is
    if (auto pl = _player1.lock()) {
        if (length(pl->getPosition() - _parent->getPosition()) < 25.0) {
            pl->setForDelete();
            _parent->setForDelete();
        }
    }

// Check if player2 is within range and set it for deletion if it is
    if (auto pl = _player2.lock()) {
        if (length(pl->getPosition() - _parent->getPosition()) < 25.0) {
            pl->setForDelete();
            _parent->setForDelete();
        }
    }
}

HurtComponent::HurtComponent(Entity* p)
        : Component(p), _player1(_parent->scene->ents.find("player")[0]), _player2(_parent->scene->ents.find("player2")[0]) {}

