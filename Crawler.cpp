//
// Created by Eric Han on 11/04/2024.
//

#include "Crawler.h"

// Constructor
Crawler::Crawler(int id, int x, int y, Direction dir, int size)
        : Bug(id, x, y, dir, size) {
    srand(static_cast<unsigned int>(time(nullptr)));
}


void Crawler::move() {
    if (isWayBlocked()) {
        int newDirection = rand() % 4 + 1;
        direction = static_cast<Direction>(newDirection);
    } else {
        switch (direction) {
            case Direction::North:
                position.second -= 1;
                break;
            case Direction::East:
                position.first += 1;
                break;
            case Direction::South:
                position.second += 1;
                break;
            case Direction::West:
                position.first -= 1;
                break;
        }
        addPath(position.first, position.second);
    }
}