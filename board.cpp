//
// Created by Eric Han on 15/04/2024.
//

#include "Board.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

board::board() {}

board::~board() {
    for (Bug* bug : bug_vector) {
        delete bug;
    }
    bug_vector.clear();
}


void board::intializeBugs(const std::string& filename) {
    ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
   string line;
    while (getline(file, line)) {
        istringstream iss(line);
        char type;
        int id, x, y, size, hopLength = 0; // Default hopLength to 0
        char delimiter; // To consume the semicolons
        string direction, status;

        iss >> type >> delimiter
            >> id >> delimiter
            >> x >> delimiter
            >> y >> delimiter
            >> direction >> delimiter
            >> size;

        if (type == 'H') {
            iss >> delimiter >> hopLength;
        }

        iss >> delimiter >> status;

        Direction dir = Direction::North; // Default
        if (direction == "East") dir = Direction::East;
        else if (direction == "South") dir = Direction::South;
        else if (direction == "West") dir = Direction::West;

        Bug* bug = nullptr;
        if (type == 'C' || type == 'c') {
            bug = new Crawler(id, x, y, dir, size);
        } else if (type == 'H' || type == 'h') {
            bug = new Hopper(id, x, y, dir, size, hopLength);
        }

        if (bug) {
            if (status == "Dead")
                bug->die();
            bug_vector.push_back(bug);
        }
    }
}


#include <iomanip> // Required for std::setw and std::left

void board::displayAllBugs() const {
    std::cout << "Display all Bugs:\n";
    std::cout << std::left; // Align all text to the left
    for (const Bug* bug : bug_vector) {
        std::string type = dynamic_cast<const Crawler*>(bug) ? "Crawler" : "Hopper";
        std::cout << std::setw(5) << bug->getID() << " "
                  << std::setw(8) << type << " "
                  << "(" << bug->getPosition().first << ","
                  << bug->getPosition().second << setw(3) << ") "
                  << std::setw(3) << bug->getSize() << " "
                  << std::setw(6) << (bug->isAlive() ? "Alive" : "Dead") << std::endl;
    }
}


