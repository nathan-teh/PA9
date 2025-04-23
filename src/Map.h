//
// Created by Karen Tinoco on 4/20/25.
//

#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Platform.h"
#include <vector>

    //Platform platform1(nullptr,sf::Vector2f(400.0f,200.0f),(sf::Vector2f(640.0f,500)));
    //Platform platform2(nullptr,sf::Vector2f(400.0f,100.0f),(sf::Vector2f(250.0f,400)));
    //platforms.push_back(&platform1);
    // platforms.push_back(&platform2);

class Map {
public:

    // brownBrick, brokenBrick, wood, greyBrick, emptyBrick
    explicit Map(float cellSize = 24.0);
    float cellSize;
    std::vector<std::vector<int>> grid;
    void loadMap(std::vector<std::unique_ptr<Platform>>& platforms,
        sf::Texture& brownBrick, sf::Texture& brokenBrick, sf::Texture& wood,
        sf::Texture& greyBrick, sf::Texture& emptyBrick, sf::Vector2f& playerPos);

};

#endif //MAP_H