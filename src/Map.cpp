//
// Created by Karen Tinoco on 4/20/25.
//

#include "Map.h"

Map::Map(float cellSize) {
    this->cellSize = cellSize;
}

void Map::loadMap(std::vector<Platform*>& platforms) {
    sf::Image image("assets/images/mapo.png");
    sf::Texture brick("assets/images/BlueBrick.png");

    //std::vector<int> name
    //grid = std::vector(image.getSize().x, std::vector(image.getSize().y, 0));

    for (unsigned int x = 0; x < 20; x++) {
        for (unsigned int y = 0; y < 60; y++) {

            sf::Color color = image.getPixel({x,y});

            if (color == sf::Color::Black) {
                  Platform temp(&brick,sf::Vector2f(50.0f,50.0f),(sf::Vector2f{static_cast<float>(x),static_cast<float>(y)}));
                  platforms.push_back(&temp); // might not work since it's deleted each time nooo
                  std::cout << "X:" << x << "  Y:" << y << std::endl;
            }

        }
    }


}
