//
// Created by Nathan Teh on 4/20/25.
//

#include "Platform.h"

Platform::Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f pos) {
    body.setTexture(texture);
    body.setOrigin(size/2.0f);
    body.setSize(size);
    body.setPosition(pos);
    this->pos=pos;
}

void Platform::Draw(sf::RenderWindow& window) {window.draw(body);}