//
// Created by Eric Han on 15/04/2024.
//
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Moth.h"
#include "Superbug.h"
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
        int hopLength = 0;
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
            case 5: dir = Direction::NorthEast; break;
            case 6: dir = Direction::SouthEast; break;
            case 7: dir = Direction::SouthWest; break;
            case 8: dir = Direction::NorthWest; break;
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
            bug = new Crawler(id, x, y, dir, size,sf::Color::Red);
        } else if (type == 'H' || type == 'h') {
            bug = new Hopper(id, x, y, dir, size, hopLength,sf::Color::Yellow);
        }else if(type =='M' || type =='m'){
            bug = new Moth(id,x,y,dir,size,sf::Color::Green);
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
//        string type = dynamic_cast<const Crawler*>(bug) ? "Crawler" : "Hopper";
        string type = bug->getType();
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
            cout << "ID: " << bug->getID() << ", Type: " << bug->getType()
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

//void board::displayAllCells() const {
//    cout << "Displaying all cells:\n";
//    for (int y = 0; y < BOARD_HEIGHT; ++y) {
//        for (int x = 0; x < BOARD_WIDTH; ++x) {
//            pair<int, int> cell(x, y);
//            cout << "(" << x << "," << y << "): ";
//            if (cellMap.find(cell) == cellMap.end() || cellMap.at(cell).empty()) {
//                cout << "empty";
//            } else {
//                for (const auto& bug : cellMap.at(cell)) {
//                    cout << (bug->getType() == "Crawler" ? "Crawler " : "Hopper ")
//                              << bug->getID() << ", ";
//                }
//            }
//            cout << endl;
//        }
//    }
//}

void board::displayAllCells() const {
    cout << "Displaying all cells:\n";
    for (int y = 0; y < BOARD_HEIGHT; ++y) {
        for (int x = 0; x < BOARD_WIDTH; ++x) {
            pair<int, int> cell(x, y);
            cout << "(" << x << "," << y << "): ";
            if (cellMap.find(cell) == cellMap.end() || cellMap.at(cell).empty()) {
                cout << "empty";
            } else {
                // Display each bug in the cell using polymorphism to get type information
                for (const auto& bug : cellMap.at(cell)) {
                    cout << bug->getType() << " " << bug->getID() << ", ";
                }
            }
            cout << endl;
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

//void board::DisplayBoardAndBug() const{
//    srand(time(NULL));
//    sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
//
//    vector<Bug> bugs; // vector of Ball structures
//    for (const auto& bug : bug_vector) {
//        bugs.emplace_back(bug->getID(), 50, sf::Color::Cyan, bug->getPosition().first, bug->getPosition().second, bug->directionToString(), bug->getSize());
//        bugs.emplace_back(bug->getID(),50,sf::Color::Black,bug->getPosition().first,bug->getPosition().second,bug->directionToString(),bug->getSize());
//        bugs.emplace_back(bug->getID(), bug->getPosition().first, bug->getPosition().second, bug->directionToString(), bug->getSize());
//
//    };
//    int size = 10;
//    vector<sf::RectangleShape> board;
//    bool blk = true;
//    for (int x = 0; x < size; x++) {
//        for (int y = 0; y < size; y++) {
//            sf::RectangleShape rect(sf::Vector2f(50, 50));
//            rect.setPosition(x * 50, y * 50);
//            if (blk) {
//                rect.setFillColor(sf::Color::Black);
//
//            } else {
//                rect.setFillColor(sf::Color::White);
//            }
//            blk = !blk;
//            board.push_back(rect);
//        }
//        blk = !blk;
//    }
//    while (window.isOpen()) {
//        sf::Event event;
//
//        // Game loop - checks for events each time
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed)
//                window.close();
//            if (event.type == sf::Event::MouseButtonReleased) {
//                if (event.mouseButton.button == sf::Mouse::Left) {
//                    for (auto &b: bugs) {
//                        b.move();
//                    }
//                }
//
//            }
//        }
//        window.clear(sf::Color::White);
//            for (const auto& rect : board) {
//                window.draw(rect);
//            }
//        for (const auto& b : bugs) {
//            sf::CircleShape shape(10.f);
//            shape.setFillColor(b.getColor());
//            shape.setPosition((b.getPosition().first * 50) + 15, (b.getPosition().second * 50) + 15);
//            window.draw(shape);
//        }Ï
//            if (event.type == sf::Event::KeyReleased) {
//                cout << event.key.code << endl;
//                cout << sf::Keyboard::C << endl;
//                if (event.key.code == sf::Keyboard::Up) {
//                    for (Ball &b: balls) {
//                        b.move();
//                    }
//                }
//            }
//
//
//        window.display();
//
//    }
//}
void board::DisplayBoardAndBug(){
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(500, 500), "Bug Simulation");
    int size = 10;  // Define the size of the board (10x10)
    int cellSize = 50;  // Each cell has a size of 50x50 pixels

    // Game loop managed here for simplicity
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Check for mouse button release
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
//                    for (auto& bug : bug_vector) {
//                        bug->move();  // Assume each bug has a move() method that updates its position
//                    }
//                    resolveConflicts();
                    int aliveCount = count_if(bug_vector.begin(), bug_vector.end(), [](const Bug* b) { return b->isAlive(); });
                    if (aliveCount > 1) {
                        TapBoard();
                    }

                }
            }
        }

        window.clear();
        // Draw the grid
        bool blk = true;
        for (int y = 0; y < size; y++) {
            for (int x = 0; x < size; x++) {
                sf::RectangleShape rect(sf::Vector2f(cellSize, cellSize));
                rect.setPosition(x * cellSize, y * cellSize);
                rect.setFillColor(blk ? sf::Color::Black : sf::Color::White);
                window.draw(rect);
                blk = !blk;
            }
            blk = !blk;
        }
        for (const auto& bug : bug_vector) {
            if (bug->isAlive()) {  // Only draw the bug if it is alive
                sf::CircleShape shape(20);
                shape.setFillColor(bug->getColor());
                auto pos = bug->getPosition();
                shape.setPosition(pos.first * cellSize + 5, pos.second * cellSize + 5);
                window.draw(shape);
            }
        }
        window.display();
    }
}




