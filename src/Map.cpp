//
// Created by Karen Tinoco on 4/20/25.
//

#include "Map.h"

Map::Map(float cellSize) {
    this->cellSize = cellSize;
}

// brownBrick, brokenBrick, wood, greyBrick, emptyBrick
void Map::loadMap(std::vector<std::unique_ptr<Platform>> &platforms, sf::Texture &brownBrick, sf::Texture &brokenBrick,
    sf::Texture &wood, sf::Texture &greyBrick, sf::Texture &emptyBrick, sf::Vector2f& playerPos) {

    sf::Image image;
    if (!image.loadFromFile("assets/images/finalMap.png")) { // map
        std::cerr << "Failed to load map image!" << std::endl;
        return;
    }

    sf::Vector2u imageSize = image.getSize();

    for (unsigned int x = 0; x < imageSize.x; x++) {
        for (unsigned int y = 0; y < imageSize.y; y++) {
            sf::Color color = image.getPixel({x, y});

            if (color == sf::Color::Black) {
                auto platform = std::make_unique<Platform>(
                    &brownBrick,
                    sf::Vector2f(cellSize, cellSize),
                    sf::Vector2f{x * cellSize, y * cellSize}
                );

                platforms.push_back(std::move(platform));
            } else if (color.r > 200 && color.g < 50 && color.b < 50) {
                //std::cout << "---RED--" << std::endl;
                playerPos = sf::Vector2f(cellSize * x + cellSize / 2.0F, cellSize * y + cellSize / 2.0F);
            }

            else if (color.r < 50 && color.g < 50 && color.b > 150) {
    // BLUE{

                auto platform = std::make_unique<Platform>(
                    &brokenBrick,
                    sf::Vector2f(cellSize, cellSize),
                    sf::Vector2f{x * cellSize, y * cellSize}
                );

                platforms.push_back(std::move(platform));
            }
            else if (color.r > 200 && color.g > 200 && color.b < 100) {

                std::cout << "Light Blue" << std::endl;

                auto platform = std::make_unique<Platform>(
                    &wood,
                    sf::Vector2f(cellSize, cellSize),
                    sf::Vector2f{x * cellSize, y * cellSize}
                );

                platforms.push_back(std::move(platform));
            }
            else if (color.g > 200 && color.r < 100 && color.b < 100) {

                auto platform = std::make_unique<Platform>(
                    &greyBrick,
                    sf::Vector2f(cellSize, cellSize),
                    sf::Vector2f{x * cellSize, y * cellSize}
                );

                platforms.push_back(std::move(platform));
            }

            else if (color.r > 200 && color.g > 100 && color.b < 50) {

                auto platform = std::make_unique<Platform>(
                    &emptyBrick,
                    sf::Vector2f(cellSize, cellSize),
                    sf::Vector2f{x * cellSize, y * cellSize}
                );

                platforms.push_back(std::move(platform));
            }
        }
    }
}
