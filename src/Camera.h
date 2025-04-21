#ifndef CAMERA_H
#define CAMERA_H
#include <SFML/Graphics.hpp>

class Camera {
public:
    Camera(float zoomLevel = 5.0);
    sf::View GetView(sf::Vector2u windowSize);

    float zoomLevel;
    sf::Vector2f position;
};


#endif //CAMERA_H
