///////////////////////////////////////////////////////////////////////////////
/// \file         Camera.cpp
/// \author       Karen Tinoco
/// \date         4/22/25
/// \brief        This file sets up the camera for Yo-Ho Jump!
///////////////////////////////////////////////////////////////////////////////

#include "Camera.h"

sf::View Camera::GetView(sf::Vector2u windowSize) {
    float aspect = static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y);
    sf::Vector2f size;
    if (aspect < 1.0f)
        size = sf::Vector2f(zoomLevel, zoomLevel / aspect);
    else
        size = sf::Vector2f(zoomLevel * aspect, zoomLevel);

    sf::Vector2f centeredPosition(windowSize.x / 2.0f, position.y); // only center X
    return sf::View(centeredPosition, size);
}