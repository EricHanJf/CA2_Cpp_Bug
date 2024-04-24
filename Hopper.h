//
// Created by Eric Han on 15/04/2024.
//

#ifndef CA2_CPP_BUG_HOPPER_H
#define CA2_CPP_BUG_HOPPER_H

using namespace std;
#include "Bug.h"

class Hopper : public Bug{
private:
        int hopLength;
public:
    Hopper(int id, int x, int y, Direction dir, int size, int hopLength);

    void move() override;
    string getType()const override;
    void changeDirectionRandomly();
};


#endif //CA2_CPP_BUG_HOPPER_H
