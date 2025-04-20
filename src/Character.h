//
// Created by Nathan Teh on 4/20/25.
//

#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include "Collider.h"

class Character {
public:
    virtual void Update(float deltaTime);
    virtual void Draw(sf::RenderWindow& window);
    //virtual Collider getCollider() {return nullptr;}

};



#endif //CHARACTER_H
