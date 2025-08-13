#include "Grid.hpp"

Grid::Grid(int windowWidth, int windowHeight, int cellSize)
    : windowWidth(windowWidth), windowHeight(windowHeight), cellSize(cellSize)
{
    cols = windowWidth/cellSize;
    rows = windowHeight/cellSize;
}

void Grid::drawGrid(sf::RenderWindow& window) {
    for (int x = 1; x < cols; x++) {
        // Draw columns
        sf::RectangleShape gridLine(sf::Vector2f(1, (float) windowHeight));
        gridLine.setPosition({cellSize*x,0});
        if (x == cols / 2) {
            gridLine.setFillColor(sf::Color::Red);
        } else {
            gridLine.setFillColor(sf::Color::Black);
        }
        window.draw(gridLine);
    }

    for (int y = 1; y < rows; y++) {
        // Draw rows
        sf::RectangleShape gridLine(sf::Vector2f((float) windowWidth, 1));
        gridLine.setPosition({0,cellSize*y});
        if (y == rows / 2) {
            gridLine.setFillColor(sf::Color::Red);
        } else {
            gridLine.setFillColor(sf::Color::Black);
        }
        window.draw(gridLine);
    }
}