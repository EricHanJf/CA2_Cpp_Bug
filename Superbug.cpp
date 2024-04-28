//
// Created by Eric Han on 25/04/2024.
//

#include "Superbug.h"

//Superbug::Superbug(int cellSize, sf::Color color) : cellSize(cellSize) {
//    shape.setRadius(25);  // Larger radius for the SuperBug
//    shape.setFillColor(color);  // Set the SuperBug's color
//    x = 5;  // Initial position
//    y = 5;  // Middle of the board
//    shape.setPosition(x * cellSize + 15, y * cellSize + 15);
//}
//
//void Superbug::handleInput() {
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && x > 0) {
//        x--;
//    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && x < 9) {
//        x++;
//    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && y > 0) {
//        y--;
//    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && y < 9) {
//        y++;
//    }
//    shape.setPosition(x * cellSize + 15, y * cellSize + 15);
//}
//
//void Superbug::interact(std::vector<Superbug>& bugs) {
//    for (Superbug& bug : bugs) {
//        if (bug.x == x && bug.y == y) {
//            bug.shape.setFillColor(sf::Color::Black); // Example interaction
//        }
//    }
//}

//void Superbug::draw(sf::RenderWindow& window) const {
//    window.draw(shape);
//}
//
//void Superbug::move(int newX, int newY) {
//    x = std::max(0, std::min(newX, 9));  // Ensure the x-coordinate is within bounds
//    y = std::max(0, std::min(newY, 9));  // Ensure the y-coordinate is within bounds
//    shape.setPosition(x * cellSize + 15, y * cellSize + 15);
//}