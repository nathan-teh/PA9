///////////////////////////////////////////////////////////////////////////////
/// \file         Collider.cpp
/// \author       Nathan Teh
/// \date         4/20/25
/// \brief        This file sets up the collider for Yo-Ho Jump!
///////////////////////////////////////////////////////////////////////////////

#include "Collider.h"

bool Collider::checkCollision(Collider& other, sf::Vector2f& direction, float push) {
    sf::Vector2f otherPosition = other.GetPosition();
    sf::Vector2f otherHalfSize = other.GetHalfSize();
    sf::Vector2f thisPosition = GetPosition();
    sf::Vector2f thisHalfSize = GetHalfSize();

    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;

    float intersectX = std::abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = std::abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

    // If collision
    if (intersectX < 0.0f && intersectY < 0.0f) {
        float pushClamped = std::min(std::max(push, 0.0f), 1.0f);

        if (std::abs(intersectX) < std::abs(intersectY)) {
            // Resolve X axis
            if (deltaX > 0.0f) {
                Move(intersectX * (1.0f - pushClamped), 0.0f);
                other.Move(-intersectX * pushClamped, 0.0f);
                direction = { 1.0f, 0.0f };
            } else {
                Move(-intersectX * (1.0f - pushClamped), 0.0f);
                other.Move(intersectX * pushClamped, 0.0f);
                direction = { -1.0f, 0.0f };
            }
        } else {
            // Resolve Y axis
            if (deltaY > 0.0f) {
                Move(0.0f, intersectY * (1.0f - pushClamped));
                other.Move(0.0f, -intersectY * pushClamped);
                direction = { 0.0f, 1.0f };
            } else {
                Move(0.0f, -intersectY * (1.0f - pushClamped));
                other.Move(0.0f, intersectY * pushClamped);
                direction = { 0.0f, -1.0f };
            }
        }

        return true;
    }

    // No collision
    direction = { 0.0f, 0.0f };
    return false;
}

