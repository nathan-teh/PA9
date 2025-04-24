///////////////////////////////////////////////////////////////////////////////
/// \file         Map.h
/// \author       Karen Tinoco
/// \date         4/20/25
/// \brief        This file sets up the map for Yo-Ho Jump!
///////////////////////////////////////////////////////////////////////////////

#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include "Platform.h"
#include <vector>

class Map {
public:
    explicit Map(float cellSize = 24.0);
    float cellSize;
    std::vector<std::vector<int>> grid;
    void loadMap(std::vector<std::unique_ptr<GameObject>> &objects,
                                sf::Texture& brownBrick,sf::Texture& brokenBrick, sf::Texture& wood,
                                            sf::Texture& greyBrick, sf::Texture& emptyBrick, sf::Vector2f& playerPos);
};

#endif //MAP_H
