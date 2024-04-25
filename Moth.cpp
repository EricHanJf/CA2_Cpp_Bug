//
// Created by Eric Han on 24/04/2024.
//

#include "Moth.h"

Moth::Moth(int id, int x, int y, Direction dir, int size)
    :Bug(id, x, y, dir, size){}

void Moth::move() {
    switch (direction) {
        case Direction::NorthEast:
            if (position.first == BOARD_WIDTH - 1 || position.second == 0) {
                direction = Direction::SouthWest; // Change to opposite diagonal
            } else {
                position.first++;
                position.second--;
            }
            break;
        case Direction::SouthEast:
            if (position.first == BOARD_WIDTH - 1 || position.second == BOARD_HEIGHT - 1) {
                direction = Direction::NorthWest;
            } else {
                position.first++;
                position.second++;
            }
            break;
        case Direction::SouthWest:
            if (position.first == 0 || position.second == BOARD_HEIGHT - 1) {
                direction = Direction::NorthEast;
            } else {
                position.first--;
                position.second++;
            }
            break;
        case Direction::NorthWest:
            if (position.first == 0 || position.second == 0) {
                direction = Direction::SouthEast;
            } else {
                position.first--;
                position.second--;
            }
            break;
    }
    addPath(position.first, position.second);
}

string Moth::getType() const const {
    return "Moth";
}

