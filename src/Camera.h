///////////////////////////////////////////////////////////////////////////////
/// \file         Camera.h
/// \author       Karen Tinoco
/// \date         4/22/25
/// \brief        This file sets up the camera for Yo-Ho Jump, including
///               logic for view creation and screen aspect ratio handling
///////////////////////////////////////////////////////////////////////////////

#ifndef CAMERA_H
#define CAMERA_H
#include <SFML/Graphics.hpp>

class Camera {
public:
    Camera(float zoomLevel = 5.0) : zoomLevel(zoomLevel) { } // constructs camera object with optional zoom level
    sf::View GetView(sf::Vector2u windowSize); // creates and returns current view based on window size

    float zoomLevel; // zoom level of camera
    sf::Vector2f position; // current camera position
};


#endif //CAMERA_H
