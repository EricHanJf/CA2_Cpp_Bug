//
// Created by Eric Han on 15/04/2024.
//

#include "Board.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
using namespace std;

board::board() {}

board::~board() {
    for (Bug* bug : bug_vector) {
        delete bug;
    }
    bug_vector.clear();
}


void board::intializeBugs(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        char type;
        int id, x, y, directionValue, size;
        int hopLength = 0;  // Default value
        char delimiter;
        string status;

        // Parse the line
        iss >> type >> delimiter
            >> id >> delimiter
            >> x >> delimiter
            >> y >> delimiter
            >> directionValue >> delimiter
            >> size;

        Direction dir = Direction::North;
        switch (directionValue) {
            case 1: dir = Direction::North; break;
            case 2: dir = Direction::East; break;
            case 3: dir = Direction::South; break;
            case 4: dir = Direction::West; break;
            default:
                cerr << "Invalid direction value: " << directionValue << endl;
                continue;  // Skip this entry if the direction is invalid
        }

        // Read hopLength only for Hopper type
        if (type == 'H' || type == 'h') {
            iss >> delimiter >> hopLength;
        }

        // Read status
        if (!(iss >> delimiter >> status)) {
            status = "Alive";  // Default status if not provided
        }

        // Create the appropriate bug type
        Bug* bug = nullptr;
        if (type == 'C' || type == 'c') {
            bug = new Crawler(id, x, y, dir, size);
        } else if (type == 'H' || type == 'h') {
            bug = new Hopper(id, x, y, dir, size, hopLength);
        }

        // If a bug was created, set its status and add to the vector
        if (bug) {
            if (status == "Dead") {
                bug->die();
            } else {
                bug->setStatus(status);
            }
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
                  << setw(3) << bug ->directionToString() << setw(3) << ""
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

void board::resolveConflicts() {
//    map<std::pair<int, int>, vector<Bug*>> positionMap;
//    for (Bug* bug : bug_vector) {
//        positionMap[bug->getPosition()].push_back(bug);
//    }
//
//    for (auto& entry : positionMap) {
//        if (entry.second.size() > 1) { // More than one bug at the same position
//            // Sort bugs by size, assume larger size means stronger bug
//            sort(entry.second.begin(), entry.second.end(), [](const Bug* a, const Bug* b) {
//                return a->getSize() > b->getSize();
//            });
//            Bug* largestBug = entry.second.front();
//            for (size_t i = 1; i < entry.second.size(); ++i) {
//                entry.second[i]->setStatus("Eaten by " + std::to_string(largestBug->getID()));
//                entry.second[i]->die(); // This sets their status to dead.
//            }
//        }
//    }

//    srand(std::time(nullptr));  // Seed for random number generation
//    for (auto& cell : cellMap) {
//        auto& bugs = cell.second;
//        if (bugs.size() > 1) {
//            std::sort(bugs.begin(), bugs.end(), [](const Bug* a, const Bug* b) {
//                return a->getSize() > b->getSize(); // Sort descending by size
//            });
//
//            Bug* largestBug = bugs.front();
//            int totalSize = largestBug->getSize();
//
//            for (size_t i = 1; i < bugs.size(); ++i) {
//                if (largestBug->getSize() == bugs[i]->getSize()) {
//                    if (rand() % 2 == 0) {  // Randomly decide winner among equals
//                        largestBug = bugs[i];
//                    }
//                }
//                totalSize += bugs[i]->getSize();
//                bugs[i]->die();
//            }
//
//            largestBug->setSize(totalSize);  // The winning bug grows
//        }
//    }

    srand(time(nullptr));  // Seed random number generator once per conflict resolution

    for (auto& cell : cellMap) {
        auto& bugs = cell.second;
        // Filter only alive bugs for processing to avoid adding dead bugs again
        vector<Bug*> aliveBugs;
        copy_if(bugs.begin(), bugs.end(), back_inserter(aliveBugs), [](Bug* b) { return b->isAlive(); });

        if (aliveBugs.size() > 1) {
            // Sort alive bugs by size, descending. Larger bugs eat smaller bugs.
            sort(aliveBugs.begin(), aliveBugs.end(), [](const Bug *a, const Bug *b) {
                return a->getSize() > b->getSize();
            });

            Bug *largestBug = aliveBugs[0];
            int totalSize = largestBug->getSize();
            for (size_t i = 1; i < aliveBugs.size(); ++i) {
                if (largestBug->getSize() == aliveBugs[i]->getSize()) {
                    // If two bugs are of the same size, randomly select the winner
                    if (rand() % 2 == 0) {
                        largestBug = aliveBugs[i];  // A new bug becomes the largest
                    }
                }
                if (aliveBugs[i]->isAlive()) {
                    totalSize += aliveBugs[i]->getSize();
                    aliveBugs[i]->setStatus("Eaten by " + to_string(largestBug->getID()));
                    aliveBugs[i]->die();  // Mark the bug as dead
                }
            }
            largestBug->setSize(totalSize);
            largestBug->setStatus("Survived");
        }
    }
}

void board::TapBoard() {
//    cout << "Tapping the Bug Board..." << endl;
//    for (Bug* bug : bug_vector) {
//        bug->move();
//    }
//    displayAllBugs();
//    resolveConflicts();
    cellMap.clear();
    for(Bug* bug: bug_vector){
        bug->move();
        cellMap[bug->getPosition()].push_back(bug);
    }
        resolveConflicts();
        displayAllBugs();
}

void board::displayBugLifeHistory() const{
    cout << "Displaying Life History of all bugs:\n";
    for (const Bug* bug : bug_vector) {
        cout << bug->getID() << " " << bug->getType() << " Path: ";
        const auto& path = bug->getPath();
        for (const auto& pos : path) {
            cout << "(" << pos.first << "," << pos.second << "), ";
        }
        cout << (bug->getStatus().empty() ? "Alive!" : bug->getStatus()) << endl;
    }
}

void board::writeLifeHistoryToFile() const {
    auto t = time(nullptr);
    auto tm = *localtime(&t);
    ostringstream oss;
    oss <<put_time(&tm, "%Y-%m-%d_%H-%M-%S");
    string fileName = "bugs_life_history_" + oss.str() + ".out";

    ofstream outFile(fileName);
    if (!outFile) {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return;
    }

    // Write data
    outFile << "Displaying Life History of all bugs:\n";
    for (const Bug* bug : bug_vector) {
        outFile << bug->getID() << " " << bug->getType() << " Path: ";
        const auto& path = bug->getPath();
        for (const auto& pos : path) {
            outFile << "(" << pos.first << "," << pos.second << "), ";
        }
        outFile << (bug->getStatus().empty() ? "Alive!" : bug->getStatus()) << std::endl;
    }
    outFile.close();
    std::cout << "Life history written to " << fileName << std::endl;
}

void board::displayAllCells() const {
    std::cout << "Displaying all cells:\n";
    for (int y = 0; y < BOARD_HEIGHT; ++y) {
        for (int x = 0; x < BOARD_WIDTH; ++x) {
            std::pair<int, int> cell(x, y);
            std::cout << "(" << x << "," << y << "): ";
            if (cellMap.find(cell) == cellMap.end() || cellMap.at(cell).empty()) {
                std::cout << "empty";
            } else {
                for (const auto& bug : cellMap.at(cell)) {
                    std::cout << (bug->getType() == "Crawler" ? "Crawler " : "Hopper ")
                              << bug->getID() << ", ";
                }
            }
            std::cout << std::endl;
        }
    }
}

void board::runSimulation() {
    bool Gamefinish = false;
    while(!Gamefinish){
        TapBoard();
        displayAllBugs();

        int aliveBug = 0;
        for(Bug* bug: bug_vector){
            if(bug ->isAlive()){
                aliveBug++;
            }
        }
        if(aliveBug <= 1){
            Gamefinish = true;
        }
    }
    cout << "Simulation ended." << endl;
    displayBugLifeHistory();
//    writeLifeHistoryToFile();
}




