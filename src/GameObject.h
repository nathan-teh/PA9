///////////////////////////////////////////////////////////////////////////////
/// \file         GameObject.h
/// \author       Nathan Teh
/// \date         4/20/25
/// \brief        This file sets up the base class for Yo-Ho Jump, where it
///               gives structure for collision-handling, updating &
///               rendering game objects (platforms, characters, etc.)
///////////////////////////////////////////////////////////////////////////////

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Collider.h"

class GameObject {
public:
    virtual ~GameObject() = default; // virtual destructor
    virtual bool IsPlatform() const { return false; } // virtual function checks if object is a platform

    virtual void Update(float deltaTime) = 0; // updates object state for current frame
    virtual void Draw(sf::RenderWindow& window) = 0; // draws object on screen
    virtual Collider* GetCollider()=0; // gets collider for an object
    virtual sf::Vector2f GetPosition() const = 0; // gets current position of object
};

#endif //GAMEOBJECT_H
