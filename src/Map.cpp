//
// Created by Karen Tinoco on 4/20/25.
//

#include "Map.h"

Map::Map(float cellSize) {
    this->cellSize = cellSize;
}




void Map::loadMap(std::vector<std::unique_ptr<Platform>>& platforms, sf::Texture& brick) {
    sf::Image image;
    if (!image.loadFromFile("assets/images/mapo.png")) {
        std::cerr << "Failed to load map image!" << std::endl;
        return;
    }

    sf::Vector2u imageSize = image.getSize();

    for (unsigned int x = 0; x < imageSize.x; x++) {
        for (unsigned int y = 0; y < imageSize.y; y++) {
            sf::Color color = image.getPixel({x, y});

            if (color == sf::Color::Black) {
                auto platform = std::make_unique<Platform>(
                    &brick,
                    sf::Vector2f(cellSize, cellSize),
                    sf::Vector2f{x * cellSize, y * cellSize}
                );

                platforms.push_back(std::move(platform));
            }
        }
    }
}
