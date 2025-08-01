#include <SFML/Graphics.hpp>

// Plan for interaction - split into grid of 512 samples. can draw, but only have one valid entry per x-axis position. allows redrawing easily
// Visually add so if two samples arent adjacent, it visually adds a vertical line between
// Once every grid is plotted, allow sound playing. with real time changing if edits are made

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({800u, 600}), "Waveform Playground");
    window.setFramerateLimit(144);

    // 1x1 rectange for cells on grid
    const int cellSize = 10;
    sf::RectangleShape cell(sf::Vector2f((float)cellSize, (float)cellSize));
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
        // Draw cells
        for (int x = 0; x < 80; x++) {
            for (int y = 0; y < 60; y++) {
                cell.setPosition({x * cellSize, y * cellSize});
                window.draw(cell);
            }
        }
        window.display();
    }
}
