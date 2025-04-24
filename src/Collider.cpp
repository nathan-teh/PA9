///////////////////////////////////////////////////////////////////////////////
/// \file         Collider.cpp
/// \author       Nathan Teh
/// \date         4/20/25
/// \brief        This file sets up the collider for Yo-Ho Jump! Includes basic 
///               AABB (Axis-Aligned Bounding Box) collision detection and resolution 
///               logic
///////////////////////////////////////////////////////////////////////////////

#include "Collider.h"

///////////////////////////////////////////////////////////////////////
/// Collider::checkCollision(Collider& other, sf::Vector2f& direction, float push)
/// \pre     colliders with proper position and size
/// \post    objects pushed apart and direction set if collision occurs
/// \param   other (other collider to check collision with); direction (vector
///          representing collision direction); push (value between 0 & 1
///          to represent how much other object is pushed)
/// \return  true if collision occurs (false otherwise)
/// \throw   none
///////////////////////////////////////////////////////////////////////
bool Collider::checkCollision(Collider& other, sf::Vector2f& direction, float push) {
    sf::Vector2f otherPosition = other.GetPosition();
    sf::Vector2f otherHalfSize = other.GetHalfSize();
    sf::Vector2f thisPosition = GetPosition();
    sf::Vector2f thisHalfSize = GetHalfSize();

    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;

    float intersectX = std::abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = std::abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

    // If collision (rectangles intersect)
    if (intersectX < 0.0f && intersectY < 0.0f) {
        float pushClamped = std::min(std::max(push, 0.0f), 1.0f); // clamp push between 0 and 1

        if (std::abs(intersectX) < std::abs(intersectY)) {
            // Resolve X axis collision
            if (deltaX > 0.0f) {
                Move(intersectX * (1.0f - pushClamped), 0.0f);
                other.Move(-intersectX * pushClamped, 0.0f);
                direction = { 1.0f, 0.0f }; // collision from the left
            } else {
                Move(-intersectX * (1.0f - pushClamped), 0.0f);
                other.Move(intersectX * pushClamped, 0.0f);
                direction = { -1.0f, 0.0f }; // collision from the right
            }
        } else {
            // Resolve Y axis collision
            if (deltaY > 0.0f) {
                Move(0.0f, intersectY * (1.0f - pushClamped));
                other.Move(0.0f, -intersectY * pushClamped);
                direction = { 0.0f, 1.0f }; // collision from the top
            } else {
                Move(0.0f, -intersectY * (1.0f - pushClamped));
                other.Move(0.0f, intersectY * pushClamped);
                direction = { 0.0f, -1.0f }; // collision from the bottom
            }
        }

        return true;
    }

    // No collision
    direction = { 0.0f, 0.0f };
    return false;
}

