//
// Created by Eric Han on 11/04/2024.
//

#include "Crawler.h"

// Constructor
Crawler::Crawler(int id, int x, int y, Direction dir, int size, sf::Color color)
        : Bug(id, x, y, dir, size, color) {
    srand(static_cast<unsigned int>(time(nullptr)));
}


//void Crawler::move() {
//    if(alive) {
//        if (isWayBlocked() || rand() % 10 < 2) {  // 20% chance to change direction
//            int newDirection = rand() % 4 + 1;
//            direction = static_cast<Direction>(newDirection);
//        }
//        if (!isWayBlocked()) {
//            switch (direction) {
//                case Direction::North:
//                    position.second -= 1;
//                    break;
//                case Direction::East:
//                    position.first += 1;
//                    break;
//                case Direction::South:
//                    position.second += 1;
//                    break;
//                case Direction::West:
//                    position.first -= 1;
//                    break;
//            }
//            addPath(position.first, position.second);
//        }
//    }
//}


void Crawler::move() {
    if(alive) {
        if (isWayBlocked() || rand() % 10 < 2) {  // 20% chance to change direction
            int newDirection = rand() % 4 + 1;
            direction = static_cast<Direction>(newDirection);
        }
//        if (isWayBlocked()) {
//            int newDirection = rand() % 4 + 1;
//            direction = static_cast<Direction>(newDirection);
//        }
        else{
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
}


string Crawler::getType() const {
    return "Crawler";
}