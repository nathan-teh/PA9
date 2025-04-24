///////////////////////////////////////////////////////////////////////////////
/// \file         Platform.cpp
/// \author       Nathan Teh
/// \date         4/20/25
/// \brief        This file sets up the platforms (static GameObjects)
///               for Yo-Ho Jump!
///////////////////////////////////////////////////////////////////////////////

#include "Platform.h"

///////////////////////////////////////////////////////////////////////
/// Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f pos)
/// \pre     none
/// \post    initializes platform with texture, size, and position;
///          sets origin to center of platform for correct rendering
/// \param   texture (pointer to texture being applied to platform);
///          size (dimesnions of the platform thru width by height);
///          pos (initial position of platform in world coordinates)
/// \return  none
/// \throw   none
///////////////////////////////////////////////////////////////////////
Platform::Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f pos) {
    body.setTexture(texture);
    body.setOrigin(size/2.0f);
    body.setSize(size);
    body.setPosition(pos);
    this->pos=pos;
}

///////////////////////////////////////////////////////////////////////
/// Draw(sf::RenderWindow& window)
/// \pre     none
/// \post    renders platform on given render window
/// \param   window (reference to SFML render window)
/// \return  none
/// \throw   none
///////////////////////////////////////////////////////////////////////
void Platform::Draw(sf::RenderWindow& window) {window.draw(body);}