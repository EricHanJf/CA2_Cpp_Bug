//
// Created by Eric Han on 24/04/2024.
//

#include "Moth.h"

Moth::Moth(int id, int x, int y, Direction dir, int size, sf::Color color)
        : Bug(id, x, y, dir, size, color) {}

void Moth::move() {
    if (!alive) return;

    // Randomly decide whether to change direction
    if (rand() % 10 < 2) {  // 20% chance to change direction
        changeDirectionRandomly();
    }

    // Try to move in the current direction
    int dx = 0, dy = 0;
    switch (direction) {
        case Direction::North:
            dy = -1;
            break;
        case Direction::NorthEast:
            dx = 1; dy = -1;
            break;
        case Direction::East:
            dx = 1;
            break;
        case Direction::SouthEast:
            dx = 1; dy = 1;
            break;
        case Direction::South:
            dy = 1;
            break;
        case Direction::SouthWest:
            dx = -1; dy = 1;
            break;
        case Direction::West:
            dx = -1;
            break;
        case Direction::NorthWest:
            dx = -1; dy = -1;
            break;
    }

    int newX = position.first + dx;
    int newY = position.second + dy;

    if (newX < 0 || newX >= BOARD_WIDTH || newY < 0 || newY >= BOARD_HEIGHT) {
        changeDirectionRandomly();
        newX = position.first;
        newY = position.second;
    } else {
        position.first = newX;
        position.second = newY;
    }

    addPath(position.first, position.second);
}


void Moth::changeDirectionRandomly() {
    int newDir = rand() % 8; // Randomly choose between 0 and 7
    switch (newDir) {
        case 0:
            direction = Direction::North;
            break;
        case 1:
            direction = Direction::NorthEast;
            break;
        case 2:
            direction = Direction::East;
            break;
        case 3:
            direction = Direction::SouthEast;
            break;
        case 4:
            direction = Direction::South;
            break;
        case 5:
            direction = Direction::SouthWest;
            break;
        case 6:
            direction = Direction::West;
            break;
        case 7:
            direction = Direction::NorthWest;
            break;
    }
}
string Moth::getType() const const {
    return "Moth";
}

