//
// Created by Nathan Teh on 4/20/25.
//

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <SFML/Graphics.hpp>
#include "Collider.h"

class GameObject {
public:
    virtual ~GameObject() = default;
    virtual bool IsPlatform() const { return false; }

    virtual void Update(float deltaTime, float& playerY) = 0;
    virtual void Draw(sf::RenderWindow& window) = 0;
    virtual Collider* GetCollider()=0;

    virtual sf::Vector2f GetPosition() const = 0;
};

#endif //GAMEOBJECT_H
