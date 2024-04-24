//
// Created by Eric Han on 10/04/2024.
//

#include "Bug.h"
#include <iostream>
using namespace std;
// Include the header file for the Bug class


// Constructor implementation
Bug::Bug(int id, int x, int y, Direction dir, int size)
        : id(id), position({x, y}), direction(dir), size(size), alive(true), status("Alive"){}


// Check if the bug's way is blocked
bool Bug::isWayBlocked() const {
    switch (direction) {
        case Direction::North:
            return position.second == 0;
        case Direction::East:
            return position.first == BOARD_WIDTH - 1;
        case Direction::South:
            return position.second == BOARD_HEIGHT - 1;
        case Direction::West:
            return position.first == 0;
    }
    return false;  // This should never be reached
}

string Bug::directionToString() const {
    switch (direction) {
        case Direction::North:
            return "North";
            break;
        case Direction::East:
            return "East";
            break;
        case Direction::South:
            return "South";
            break;
        case Direction::West:
            return "West";
            break;
        default:
            return "Unknown";
//        case Direction::North: return "North" break;
//        case Direction::East:  return "East";
//        case Direction::South: return "South";
//        case Direction::West:  return "West";
//        default:               return "Unknown";
    }
}

int Bug::getID() const {
    return id;
}

int Bug::getSize() const {
    return size;
}

std::pair<int, int> Bug::getPosition() const {
    return position;
}

bool Bug::isAlive() const {
    return alive;
}

void Bug::die() {
    alive = false;
//    if(status =="Alive"){
//        status = "Dead";
//    }
}

void Bug::addPath(int x, int y) {
    path.push_back(make_pair(x, y));
}

void Bug::setStatus(const string& newstatus){
    status = newstatus;
}

string Bug::getStatus() const {
    return status;
}

const list<std::pair<int, int>>& Bug::getPath() const {
    return path;
}

void Bug::setSize(int newSize) {
     size = newSize;
}


