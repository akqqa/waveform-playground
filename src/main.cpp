#include <SFML/Graphics.hpp>

// Plan for interaction - split into grid of 512 samples. can draw, but only have one valid entry per x-axis position. allows redrawing easily
// Visually add so if two samples arent adjacent, it visually adds a vertical line between
// Once every grid is plotted, allow sound playing. with real time changing if edits are made

const float multiplier = 1;
const int windowWidth = 960*multiplier;
const int windowHeight = 540*multiplier;
const int cellSize = 10*multiplier;

// SLOW due to current method of drawing 1000s of cells. Replace with grid lines
// Also put into proper classes

auto window = sf::RenderWindow(sf::VideoMode({windowWidth, windowHeight}), "Waveform Playground");

// 1x1 rectange for cells on grid
sf::RectangleShape cell(sf::Vector2f((float)cellSize, (float)cellSize));
// Central line
sf::RectangleShape line(sf::Vector2f((float)windowWidth, cellSize/4));

void drawGrid() {
        // Draw cells
        for (int x = 0; x < windowWidth/cellSize; x++) {
            for (int y = 0; y < windowHeight/cellSize; y++) {
                cell.setFillColor(sf::Color::White);
                cell.setPosition({x * cellSize, y * cellSize});
                window.draw(cell);
            }
        }
        // Draw mouse cell
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        cell.setPosition({mousePos.x - (mousePos.x%cellSize), mousePos.y - (mousePos.y%cellSize)});
        cell.setFillColor(sf::Color::Black);
        window.draw(cell);
        // Draw central line
        line.setFillColor(sf::Color::Red);
        line.setPosition({0, windowHeight/2 - cellSize/8});
        window.draw(line);
        

}

int main()
{
    window.setFramerateLimit(144);

    cell.setOutlineColor(sf::Color::Black);
    cell.setOutlineThickness(1.f);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();
        drawGrid();
        window.display();
    }
}