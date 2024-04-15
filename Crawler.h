//
// Created by Eric Han on 11/04/2024.
//

#ifndef CA2_CPP_BUG_CRAWLER_H
#define CA2_CPP_BUG_CRAWLER_H
#include "Bug.h"
#include <cstdlib>
#include <ctime>
using namespace std;


class Crawler : public Bug {

public:
    Crawler(int id, int x, int y, Direction dir, int size);

    void move() override;
};


#endif //CA2_CPP_BUG_CRAWLER_H
