#pragma once
#include <SFML/Graphics.hpp>

class MouseHandler {
    public:
        MouseHandler(int cellSize);

        void update(sf::RenderWindow& window);

        void drawMouse(sf::RenderWindow& window, sf::RectangleShape& cell);

        sf::Vector2i getPosition() const;
        sf::Vector2i getPositionCell(sf::RenderWindow& window) const;
        bool isLeftPressed() const;

    private:
        sf::Vector2i position;
        bool leftPressed;
        int cellSize;
};