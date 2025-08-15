#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Grid.hpp"
#include "MouseHandler.hpp"
#include "SoundHandler.hpp"
#include <cmath>
#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>

// Plan for interaction - split into grid of 512 samples. can draw, but only have one valid entry per x-axis position. allows redrawing easily
// Visually add so if two samples arent adjacent, it visually adds a vertical line between
// Once every grid is plotted, allow sound playing. with real time changing if edits are made

// TODO: Add array of values to grid, update the array based on mouse pos and clicked

const float multiplier = 1;
const int windowWidth = 960*2*multiplier;
const int windowHeight = 540*2*multiplier;
const int cellSize = 10*multiplier;
int maxAmplitude = windowHeight/cellSize;

auto window = sf::RenderWindow(sf::VideoMode({windowWidth, windowHeight}), "Waveform Playground");

// 1x1 rectange for cells on grid
sf::RectangleShape cell(sf::Vector2f((float)cellSize, (float)cellSize));
// Central line
sf::RectangleShape line(sf::Vector2f((float)windowWidth, cellSize/4));

void draw(sf::RenderWindow& window, Grid& grid, MouseHandler& mouseHandler) {
    // Draw mouse cell
    grid.drawGrid(window, cell);
    mouseHandler.drawMouse(window, cell);
}

std::vector<std::int16_t> convertCellData(std::vector<int>& cellData) {
    std::vector<std::int16_t> audioData;
    audioData.resize(cellData.size());
    for (int i = 0; i < cellData.size(); i++) {
        int64_t temp = static_cast<int64_t>(cellData[i]) * 65535;
        int16_t mapped = 32767 - static_cast<int16_t>(temp / maxAmplitude);
        audioData[i] = mapped;
    }

    return audioData;
}

int main()
{
    window.setFramerateLimit(500);
    window.setMouseCursorVisible(false);

    Grid grid(windowWidth, windowHeight, cellSize);
    MouseHandler mouseHandler(cellSize);
    SoundHandler sound;
    sound.play();

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
        mouseHandler.update(window);
        if (mouseHandler.isLeftPressed()) {
            sf::Vector2i cellPos = mouseHandler.getPositionCell(window);
            std::cout << "Position: (" << cellPos.x << ", " << cellPos.y << ")" << std::endl;
            grid.setCell(cellPos.x, cellPos.y);
            // convert cellData to audioData and update waveform in soundhandler
            std::vector<int> cellData = grid.getCellData();
            if (! std::any_of(cellData.begin(), cellData.end(), [](int x){ return x == -1; })) {
                sound.updateWaveform(convertCellData(cellData));
            }

        }
        draw(window, grid, mouseHandler);
        window.display();
    }
}