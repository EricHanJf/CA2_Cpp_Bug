//
// Created by Eric Han on 10/04/2024.
//

#ifndef CA2_CPP_BUG_BUG_H
#define CA2_CPP_BUG_BUG_H
#include <iostream>
#include <list>
using namespace std;

enum class Direction {North = 1, East = 2, South = 3, West = 4,NorthEast=5, SouthEast=6, SouthWest=7, NorthWest=8};
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
    string status;

public:
    Bug(int id, int x, int y, Direction dir, int size);
    virtual ~Bug() = default;
    virtual void move() = 0;
    virtual string getType() const = 0;
    string directionToString() const ;

    bool isWayBlocked() const ;
    int getID() const ;
    int getSize() const;
    pair<int, int> getPosition() const ;
    bool isAlive() const ;
    void die();
    void addPath(int x, int y);
    void setStatus(const string& newstatus);
    string getStatus() const;
    const list<pair<int, int>>& getPath() const;
    void setSize(int newSize);
};

#endif //CA2_CPP_BUG_BUG_H
