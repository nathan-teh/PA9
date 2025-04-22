//
// Created by Karen Tinoco on 4/20/25.
//

#include "Map.h"

Map::Map(float cellSize) {
    this->cellSize = cellSize;
}


void Map::loadMap(std::vector<std::unique_ptr<Platform>> &platforms, sf::Texture &blue, sf::Texture &lightBlue,
    sf::Texture &green, sf::Texture &yellow, sf::Texture &purple, sf::Vector2f& playerPos) {

    sf::Image image;
    if (!image.loadFromFile("assets/images/m11.png")) { // map
        std::cerr << "Failed to load map image!" << std::endl;
        return;
    }

    sf::Vector2u imageSize = image.getSize();

    for (unsigned int x = 0; x < imageSize.x; x++) {
        for (unsigned int y = 0; y < imageSize.y; y++) {
            sf::Color color = image.getPixel({x, y});

            if (color == sf::Color::Black) {
                auto platform = std::make_unique<Platform>(
                    &blue,
                    sf::Vector2f(cellSize, cellSize),
                    sf::Vector2f{x * cellSize, y * cellSize}
                );

                platforms.push_back(std::move(platform));
            } else if (color.r > 200 && color.g < 50 && color.b < 50) {
                //std::cout << "---RED--" << std::endl;
                playerPos = sf::Vector2f(cellSize * x + cellSize / 2.0F, cellSize * y + cellSize / 2.0F);
            }

            else if (color.r > 120 && color.b > 100 && color.g < 100) {

                auto platform = std::make_unique<Platform>(
                    &purple,
                    sf::Vector2f(cellSize, cellSize),
                    sf::Vector2f{x * cellSize, y * cellSize}
                );

                platforms.push_back(std::move(platform));
            }
            else if (color.b > 200 && color.r < 100 && color.g > 200) {

                std::cout << "Light Blue" << std::endl;

                auto platform = std::make_unique<Platform>(
                    &lightBlue,
                    sf::Vector2f(cellSize, cellSize),
                    sf::Vector2f{x * cellSize, y * cellSize}
                );

                platforms.push_back(std::move(platform));
            }
            else if (color.r > 200 && color.g > 100 && color.b < 80) {

                auto platform = std::make_unique<Platform>(
                    &yellow,
                    sf::Vector2f(cellSize, cellSize),
                    sf::Vector2f{x * cellSize, y * cellSize}
                );

                platforms.push_back(std::move(platform));
            }
            else if (color.b > 150 && color.r > 100 && color.g < 100) {

                auto platform = std::make_unique<Platform>(
                    &lightBlue,
                    sf::Vector2f(cellSize, cellSize),
                    sf::Vector2f{x * cellSize, y * cellSize}
                );

                platforms.push_back(std::move(platform));
            }
        }
    }
}
