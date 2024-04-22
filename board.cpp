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


void board::displayAllBugs() const {
    cout << "Display all Bugs:\n";
    cout << left;
    for (const Bug* bug : bug_vector) {
        string type = dynamic_cast<const Crawler*>(bug) ? "Crawler" : "Hopper";
        cout << setw(5) << bug->getID() << " "
                  << setw(8) << type << " "
                  << "(" << bug->getPosition().first << ","
                  << bug->getPosition().second << setw(3) << ") "
                  << setw(3) << bug->getSize() << " "
                  << setw(6) << (bug->isAlive() ? "Alive" : "Dead") << endl;
    }
}

void board::findAndDisplayBug(int id) const{
    for(const Bug* bug: bug_vector){
        if(bug ->getID() == id){
            cout << "Bug found: \n";
            cout << "ID: " << bug->getID() << ", Type: "
            << (dynamic_cast<const Crawler*>(bug)? "Crawler": "Hopper")
            << ", Position: (" << bug->getPosition().first << "," << bug->getPosition().second
            << "), Size: " << bug->getSize()
            << ", Status: " << (bug->isAlive() ? "Alive" : "Dead") << endl;
            return;
        }
    }
    cout << "Bug Id: "<< id << " Not found" <<endl;
}

void board::TapBoard() {
    std::cout << "Tapping the Bug Board..." << std::endl;
    for (Bug* bug : bug_vector) {
        bug->move();
    }
    displayAllBugs();
}

