//
// Created by Eric Han on 15/04/2024.
//

#ifndef CA2_CPP_BUG_BOARD_H
#define CA2_CPP_BUG_BOARD_H
#include <vector>
#include "Bug.h"
#include "Crawler.h"
#include "Hopper.h"
using namespace std;


class board {
private:
    vector<Bug*> bug_vector;

public:
    board();
    ~board();

    void intializeBugs(const string &filename);
    vector<Bug*> getBugs() const;
    void displayAllBugs() const;
};


#endif //CA2_CPP_BUG_BOARD_H