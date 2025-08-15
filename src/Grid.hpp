#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Grid {
    public:
        Grid(int windowWidth, int windowHeight, int cellSize);

        void drawGrid(sf::RenderWindow& window, sf::RectangleShape& cell);

        void setCell(int col, int row);

        std::vector<int> getCellData();
        

    private:
        int cols, rows, cellSize, windowWidth, windowHeight;
        sf::RectangleShape gridLine;
        std::vector<int> cellData; // Celldata is represented by an array each representing a column, and the integer representing which row of the column is selected
};