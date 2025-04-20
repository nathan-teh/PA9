#ifndef CAMERA
#define CAMERA

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class Camera {
    public:
    Camera(float zoomLevel = 5.0);
    sf::View GetView(sf::Vector2u windowSize);

    float zoomLevel;
    sf::Vector2f position;
};

#endif