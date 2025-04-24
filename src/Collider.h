///////////////////////////////////////////////////////////////////////////////
/// \file         Collider.h
/// \author       Nathan Teh
/// \date         4/20/25
/// \brief        This file sets up the collider for Yo-Ho Jump! Includes basic 
///               AABB (Axis-Aligned Bounding Box) collision detection and resolution 
///               logic
///////////////////////////////////////////////////////////////////////////////

#ifndef COLLIDER_H
#define COLLIDER_H
#include <SFML/Graphics.hpp>

class Collider {
public:
    Collider(sf::RectangleShape& body) : body(body) {}; // collider initialized with reference to rectangle shape
    ~Collider() = default; // destructor
    void Move(float dx, float dy) {body.move(sf::Vector2f(dx, dy));} // moves rectangle shape by delta (in x or y direction)
    bool checkCollision(Collider& other, sf::Vector2f& direction,float push); // checks collision with another collider and returns collision direction
    sf::Vector2f GetPosition() {return body.getPosition();} // gets position of rectangle shape
    sf::Vector2f GetHalfSize() {return body.getSize()/2.0f;} // gets half size of rectangle shape

private:
    sf::RectangleShape& body; // reference to rectangle shape this collider manages
};



#endif //COLLIDER_H
