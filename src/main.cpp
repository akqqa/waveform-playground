#include <SFML/Graphics.hpp>
#include "Grid.hpp"

// Plan for interaction - split into grid of 512 samples. can draw, but only have one valid entry per x-axis position. allows redrawing easily
// Visually add so if two samples arent adjacent, it visually adds a vertical line between
// Once every grid is plotted, allow sound playing. with real time changing if edits are made

const float multiplier = 1;
const int windowWidth = 960*multiplier;
const int windowHeight = 540*multiplier;
const int cellSize = 10*multiplier;

auto window = sf::RenderWindow(sf::VideoMode({windowWidth, windowHeight}), "Waveform Playground");

// 1x1 rectange for cells on grid
sf::RectangleShape cell(sf::Vector2f((float)cellSize, (float)cellSize));
// Central line
sf::RectangleShape line(sf::Vector2f((float)windowWidth, cellSize/4));

void draw() {
    // Draw mouse cell
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    cell.setPosition({mousePos.x - (mousePos.x%cellSize), mousePos.y - (mousePos.y%cellSize)});
    cell.setFillColor(sf::Color::Black);
    window.draw(cell);
}

int main()
{
    window.setFramerateLimit(144);

    // cell.setOutlineColor(sf::Color::Black);
    // cell.setOutlineThickness(1.f);

    Grid grid(windowWidth, windowHeight, cellSize);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear(sf::Color::White);
        grid.drawGrid(window);
        draw();
        window.display();
    }
}