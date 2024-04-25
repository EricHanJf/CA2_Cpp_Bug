//
// Created by Eric Han on 15/04/2024.
//

#include "Hopper.h"
using namespace std;


Hopper::Hopper(int id, int x, int y, Direction dir, int size, int hopLength)
        : Bug(id, x, y, dir, size), hopLength(hopLength) {}


void Hopper::move() {
    bool moved = false;
    int attempts = 0;

//    for (int i = 0; i < hopLength; ++i) {
//        if (isWayBlocked()) {
//            break;
//        }
    while (!moved && attempts < 4) {  // Try up to 4 different directions
        for (int i = 0; i < hopLength; ++i) {
            if (isWayBlocked()) {
                // If blocked, try a new random direction if not moved yet
                if (i == 0) {
                    changeDirectionRandomly();
                    break;  // Exit the for-loop and try a new direction
                } else {
                    // If it moved at least once, stop moving this turn
                    addPath(position.first, position.second);
                    return;
                }
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
            moved = true;
        }
        if(moved) {
            addPath(position.first, position.second);
        }
        attempts++;
    }
}

void Hopper::changeDirectionRandomly() {
    srand(std::time(nullptr));
    int newDirection = rand() % 4 + 1;
    direction = static_cast<Direction>(newDirection);
}

string Hopper::getType() const {
    return "Hopper";
}
