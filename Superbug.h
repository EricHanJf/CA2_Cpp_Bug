//
// Created by Eric Han on 25/04/2024.
//

#ifndef CA2_CPP_BUG_SUPERBUG_H
#define CA2_CPP_BUG_SUPERBUG_H


//#include <SFML/Graphics/CircleShape.hpp>
//#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "Bug.h"

class Superbug : public Bug{
//    Superbug(int id, int size, sf::Color color, int x, int y, Direction dir, int cellSize);
//    sf::CircleShape shape;
//    int x, y;
//    int cellSize;
//    Superbug(int cellSize, sf::Color color);
//    void handleInput();
//    void interact(std::vector<Superbug>& bugs);
//    void draw(sf::RenderWindow& window) const;
//private:
//    void move(int newX, int newY);

private:
    void move(int newX, int newY);
    sf::CircleShape shape;
    int cellSize;
public:
    Superbug(int id, int size, sf::Color color, int x, int y, Direction dir, int cellSize);
    void handleInput();
    void interact(std::vector<Superbug>& bugs);
    void draw(sf::RenderWindow& window) const;
};


#endif //CA2_CPP_BUG_SUPERBUG_H
