//
// Created by Eric Han on 15/04/2024.
//

#ifndef CA2_CPP_BUG_BOARD_H
#define CA2_CPP_BUG_BOARD_H
#include <vector>
#include <map>
#include "Bug.h"
#include "Crawler.h"
#include "Hopper.h"
using namespace std;


class board {
private:
    vector<Bug*> bug_vector;
    map<pair<int, int>, vector<Bug*>> cellMap;
public:
    board();
    ~board();

    void intializeBugs(const string &filename);
    vector<Bug*> getBugs() const;
    void displayAllBugs() const;
    void findAndDisplayBug(int id) const;
    void resolveConflicts();
    void TapBoard();
    void displayBugLifeHistory() const;
    void writeLifeHistoryToFile() const;
    void displayAllCells() const;
    void runSimulation();

};


#endif //CA2_CPP_BUG_BOARD_H
