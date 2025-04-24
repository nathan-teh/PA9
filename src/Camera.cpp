///////////////////////////////////////////////////////////////////////////////
/// \file         Camera.cpp
/// \author       Karen Tinoco
/// \date         4/22/25
/// \brief        This file sets up the camera for Yo-Ho Jump, including
///               logic for view creation and screen aspect ratio handling
///////////////////////////////////////////////////////////////////////////////

#include "Camera.h"

///////////////////////////////////////////////////////////////////////
/// GetView(sf::Vector2u windowSize)
/// \pre     none
/// \post    returns "sf::View" object for rendering scene
/// \param   windowSize (size of game window thru width by height)
/// \return  "sf::View" object that represents camera view
/// \throw   none
///////////////////////////////////////////////////////////////////////
sf::View Camera::GetView(sf::Vector2u windowSize) {
    // calculate window's aspect ratio by dividing height from width (width / height)
    float aspect = static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y);
    sf::Vector2f size;

    // set view size based on aspect ratio & zoom level
    if (aspect < 1.0f)
        size = sf::Vector2f(zoomLevel, zoomLevel / aspect); // taller
    else
        size = sf::Vector2f(zoomLevel * aspect, zoomLevel); // wider
    
    // centers view on x-axis only; y is based on camera's position
    sf::Vector2f centeredPosition(windowSize.x / 2.0f, position.y);
    return sf::View(centeredPosition, size);
}