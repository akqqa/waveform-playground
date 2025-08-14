#include "Grid.hpp"
#include <cmath>

Grid::Grid(int windowWidth, int windowHeight, int cellSize)
    : windowWidth(windowWidth), windowHeight(windowHeight), cellSize(cellSize)
{
    cols = windowWidth/cellSize;
    rows = windowHeight/cellSize;

    cellData.resize(cols, -1);
}

void Grid::drawGrid(sf::RenderWindow& window, sf::RectangleShape& cell) {
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

    // Draw celldata
    for (int i = 0; i < cols; i++) {
        if (cellData[i] == -1) {continue;}
        cell.setPosition({i*cellSize, cellData[i]*cellSize});
        cell.setFillColor(sf::Color::Black);
        window.draw(cell);
        // Draw connection between last cell if there is a gap - cant quite get spikes right. tried not drawing reversals but didnt work in cases where reversals were wanted
        if (i !=0 && cellData[i-1] != -1 && std::abs(cellData[i-1] - cellData[i]) > 1) {
            
            if (cellData[i-1] < cellData[i]) { // cells are going down
                for (int j = cellData[i-1] + 1; j < cellData[i]; j++) {
                    cell.setPosition({i*cellSize, j*cellSize});
                    cell.setFillColor(sf::Color::Black);
                    window.draw(cell);
                }
            } else {
                for (int j = cellData[i-1] - 1; j > cellData[i]; j--) {
                    cell.setPosition({i*cellSize, j*cellSize});
                    cell.setFillColor(sf::Color::Black);
                    window.draw(cell);
                }
            }
        }
    }

}

void Grid::setCell(int col, int row) {
    if (col < 0 || col >= cols || row < 0 || row >= rows) return;

    cellData[col] = row;
}