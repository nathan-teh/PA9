#ifndef MAP
#define MAP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <box2d/box2d.h>

#include "renderer.hpp"
#include "player.hpp"
#include "Physics.hpp"

class Map {
    public:
    Map(float cellSize = 32.0);
    void Draw(Renderer& renderer);
    
    sf::Vector2f CreateFromImage(const sf::Image& image);

    std::vector<std::vector<int>> grid;
    float cellSize;

};

#endif