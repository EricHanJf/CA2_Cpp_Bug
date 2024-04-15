//
// Created by Eric Han on 10/04/2024.
//

#ifndef CA2_CPP_BUG_BUG_H
#define CA2_CPP_BUG_BUG_H
#include <iostream>
#include <list>
using namespace std;

enum class Direction {North, East, South, West};
const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 10;

class Bug {
protected:
    int id;
    pair<int, int> position;
    Direction direction;
    int size;
    bool alive;
    list<pair<int,int>> path;

public:
    Bug(int id, int x, int y, Direction dir, int size);
    virtual ~Bug() = default;
    virtual void move() = 0;
    bool isWayBlocked() const ;
    int getID() const ;
    pair<int, int> getPosition() const ;
    bool isAlive() const ;
    void die();
    void addPath(int x, int y);

};


#endif //CA2_CPP_BUG_BUG_H
