//
// Created by Eric Han on 15/04/2024.
//

#include "Hopper.h"


// Constructor
Hopper::Hopper(int id, int x, int y, Direction dir, int size, int hopLength)
        : Bug(id, x, y, dir, size), hopLength(hopLength) {}

// Move method specific to Hopper
void Hopper::move() {
    for (int i = 0; i < hopLength; ++i) {
        if (isWayBlocked()) {
            break;
        }
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
