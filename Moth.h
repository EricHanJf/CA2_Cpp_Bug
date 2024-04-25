//
// Created by Eric Han on 24/04/2024.
//

#ifndef CA2_CPP_BUG_MOTH_H
#define CA2_CPP_BUG_MOTH_H


#include "Bug.h"
using namespace std;

class Moth : public Bug{

public:
    Moth(int id, int x, int y,Direction dir, int size);

    void move() override;
    string getType() const override;

};


#endif //CA2_CPP_BUG_MOTH_H
