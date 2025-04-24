///////////////////////////////////////////////////////////////////////////////
/// \file         Platform.cpp
/// \author       Nathan Teh
/// \date         4/20/25
/// \brief        This file sets up the platforms for Yo-Ho Jump!
///////////////////////////////////////////////////////////////////////////////

#include "Platform.h"

Platform::Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f pos) {
    body.setTexture(texture);
    body.setOrigin(size/2.0f);
    body.setSize(size);
    body.setPosition(pos);
    this->pos=pos;
}

void Platform::Draw(sf::RenderWindow& window) {window.draw(body);}