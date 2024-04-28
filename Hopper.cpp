//
// Created by Eric Han on 15/04/2024.
//

#include "Hopper.h"
using namespace std;



Hopper::Hopper(int id, int x, int y, Direction dir, int size, int hopLength, sf::Color color)
        : Bug(id, x, y, dir, size, color) {
    srand(time(NULL));
}

void Hopper::move() {
    if (!alive) return; // If not alive, do not proceed with the move.
    bool moved = false;
    int attempts = 0;

    while (!moved && attempts < 4) {
        int steps = 0;
        while (steps < hopLength) {
            // Execute movement based on the current direction
            switch (direction) {
                case Direction::North:
                    position.second--;
                    break;
                case Direction::East:
                    position.first++;
                    break;
                case Direction::South:
                    position.second++;
                    break;
                case Direction::West:
                    position.first--;
                    break;
            }
            steps++;
            // Check if the way is blocked after moving
            if (isWayBlocked()) {
                switch (direction) {
                    case Direction::North:
                        position.second++;
                        break;
                    case Direction::East:
                        position.first--;
                        break;
                    case Direction::South:
                        position.second--;
                        break;
                    case Direction::West:
                        position.first++;
                        break;
                }
                break;
            }
            moved = true; // Flag that movement has happened
        }

        if (!moved) {
            changeDirectionRandomly();
        } else {
            addPath(position.first, position.second);
        }
        attempts++;
    }

    if (moved) {
        addPath(position.first, position.second);
    }
}




void Hopper::changeDirectionRandomly() {
//    srand(std::time(nullptr));
//    int newDirection = rand() % 4 + 1;
//    direction = static_cast<Direction>(newDirection);

    int newDirection;
    do {
        newDirection = std::rand() % 4 + 1; // Ensure new direction is different
    } while (newDirection == static_cast<int>(direction));

    direction = static_cast<Direction>(newDirection);
}

string Hopper::getType() const {
    return "Hopper";
}
