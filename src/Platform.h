//
// Created by Nathan Teh on 4/20/25.
//

#ifndef PLATFORM_H
#define PLATFORM_H

#include <SFML/Graphics.hpp>
#include "Collider.h"


class Platform {
public:
    Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f pos);
    ~Platform();

    void Draw(sf::RenderWindow& window);
    Collider* GetCollider(){return new Collider(body);}
private:
    sf::RectangleShape body;

};



#endif //PLATFORM_H
