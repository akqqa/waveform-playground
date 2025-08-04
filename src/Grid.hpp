#pragma once
#include <SFML/Graphics.hpp>

class Grid {
    public:
        Grid(int windowWidth, int windowHeight, int cellSize);

        void drawGrid(sf::RenderWindow& window);

    private:
        int cols, rows, cellSize, windowWidth, windowHeight;
        sf::RectangleShape gridLine;
};