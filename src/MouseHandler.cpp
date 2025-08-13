#include "MouseHandler.hpp"
#include <cmath>

MouseHandler::MouseHandler(int cellSize)
    : cellSize(cellSize)
{}

void MouseHandler::update(const sf::RenderWindow& window) {
    position = sf::Mouse::getPosition(window);
    leftPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

void MouseHandler::drawMouse(sf::RenderWindow& window, sf::RectangleShape& cell) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
    cell.setPosition({worldPos.x - std::fmod(worldPos.x, cellSize), worldPos.y - std::fmod(worldPos.y, cellSize)});
    cell.setFillColor(sf::Color::Black);
    window.draw(cell);
}

sf::Vector2i MouseHandler::getPosition() const { return position; }
bool MouseHandler::isLeftPressed() const { return leftPressed; }
