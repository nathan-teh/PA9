///////////////////////////////////////////////////////////////////////////////
/// \file         Map.cpp
/// \author       Karen Tinoco
/// \date         4/20/25
/// \brief        This file sets up the map for Yo-Ho Jump! Loads map image,
///               processes the pixels and creates game objects based on pixel 
///               colors.
///////////////////////////////////////////////////////////////////////////////

#include "Map.h"
#include <iostream>

///////////////////////////////////////////////////////////////////////
/// Map(float cellSize)
/// \pre     none
/// \post    initializes map with specific cell size, determining dimensions
///          of each platform and object in the game
/// \param   cellSize (pixel size of each cell in map grid)
/// \return  none
/// \throw   none
///////////////////////////////////////////////////////////////////////
Map::Map(float cellSize) {
    this->cellSize = cellSize;
}

///////////////////////////////////////////////////////////////////////
/// loadMap(std::vector<std::unique_ptr<GameObject>> &objects, sf::Texture 
/// &brownBrick, sf::Texture &brokenBrick, sf::Texture& wood, sf::Texture& 
/// greyBrick, sf::Texture& emptyBrick, sf::Vector2f& playerPos)
/// \pre     provided textures are loaded and valid
/// \post    objects vector populated with Platform objects, playerPos set
///          to player's starting position based on map color data
/// \param objects (vector of unique pointers to `GameObject` holding platform 
///                 objects created from the map image)
/// \param brownBrick (texture used for creating brown brick platforms)
/// \param brokenBrick (texture used for creating broken brick platforms)
/// \param wood        (texture used for creating wooden platforms)
/// \param greyBrick   (texture used for creating grey brick platforms)
/// \param emptyBrick  (texture used for creating empty (background) platforms)
/// \param playerPos   (reference to a vector representing the player's initial 
///                    position)
/// \return  none
///////////////////////////////////////////////////////////////////////
void Map::loadMap(std::vector<std::unique_ptr<GameObject>> &objects, sf::Texture &brownBrick, sf::Texture &brokenBrick,
    sf::Texture &wood, sf::Texture &greyBrick, sf::Texture &emptyBrick, sf::Vector2f& playerPos) {

    // load map image from file
    sf::Image image;
    if (!image.loadFromFile("assets/images/mappyy.png")) { // map
        std::cerr << "Failed to load map image!" << std::endl;
        return;
    }

    // get dimensions of map image
    sf::Vector2u imageSize = image.getSize();

    // iterate each pixel in map image
    for (unsigned int x = 0; x < imageSize.x; x++) {
        for (unsigned int y = 0; y < imageSize.y; y++) {
            sf::Color color = image.getPixel({x, y});

            // create platform based on pixel color
            if (color == sf::Color::Black) {
                // black pixels represent brown brick platforms
                objects.push_back(std::make_unique<Platform>(
                    &brownBrick,
                    sf::Vector2f(cellSize, cellSize),
                    sf::Vector2f{x * cellSize, y * cellSize})
                );
            } else if (color.r > 200 && color.g < 50 && color.b < 50) {
                // red = player's spawn position
                playerPos = sf::Vector2f(cellSize * x + cellSize / 2.0F, cellSize * y + cellSize / 2.0F);
            }
            else if (color.r < 50 && color.g < 50 && color.b > 150) {
                // blue pixels = broken brick platforms
                objects.push_back(std::make_unique<Platform>(
                    &brokenBrick,
                    sf::Vector2f(cellSize, cellSize),
                    sf::Vector2f{x * cellSize, y * cellSize})
                );
            }
            else if (color.r > 200 && color.g > 200 && color.b < 100) {
                // yellow-green pixels = wooden platforms
                objects.push_back(std::make_unique<Platform>(
                    &wood,
                    sf::Vector2f(cellSize, cellSize),
                    sf::Vector2f{x * cellSize, y * cellSize})
                );
            }
            else if (color.g > 200 && color.r < 100 && color.b < 100) {
                // green pixels = grey brick platforms
                objects.push_back(std::make_unique<Platform>(
                    &greyBrick,
                    sf::Vector2f(cellSize, cellSize),
                    sf::Vector2f{x * cellSize, y * cellSize})
                );
            }
            else if (color.r > 200 && color.g > 100 && color.b < 50) {
                // orange pixels = empty (background) platforms
                objects.push_back(std::make_unique<Platform>(
                    &emptyBrick,
                    sf::Vector2f(cellSize, cellSize),
                    sf::Vector2f{x * cellSize, y * cellSize})
                );
            }
        }
    }
}
