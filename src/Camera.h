///////////////////////////////////////////////////////////////////////////////
/// \file         Camera.h
/// \author       Karen Tinoco
/// \date         4/22/25
/// \brief        This file sets up the camera for Yo-Ho Jump!
///////////////////////////////////////////////////////////////////////////////

#ifndef CAMERA_H
#define CAMERA_H
#include <SFML/Graphics.hpp>

class Camera {
public:
    Camera(float zoomLevel = 5.0) : zoomLevel(zoomLevel) { }
    sf::View GetView(sf::Vector2u windowSize);

    float zoomLevel;
    sf::Vector2f position;
};


#endif //CAMERA_H
