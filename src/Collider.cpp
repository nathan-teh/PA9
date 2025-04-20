//
// Created by Nathan Teh on 4/20/25.
//

#include "Collider.h"

bool Collider::checkCollision(Collider& other, float push) {
    sf::Vector2f otherPosition=other.GetPosition();
    sf::Vector2f otherHalfSize=other.GetHalfSize();
    sf::Vector2f thisPosition=GetPosition();
    sf::Vector2f thisHalfSize=GetHalfSize();

    float deltaX=otherPosition.x-thisPosition.x;
    float deltaY=otherPosition.y-thisPosition.y;
    float intersectX=abs(deltaX)-(otherHalfSize.x+thisHalfSize.x);
    float intersectY=abs(deltaY)-(otherHalfSize.y+thisHalfSize.y);
    float overlapX = std::abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float overlapY = std::abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

    if (overlapX < 0.0f && overlapY < 0.0f) {
        float pushClamped = std::min(std::max(push, 0.0f), 1.0f);

        // Which axis do we resolve?
        if (std::abs(overlapX) < std::abs(overlapY)) {
            // Resolve X-axis
            if (deltaX > 0.0f) {
                Move(overlapX * (1.0f - pushClamped), 0.0f);
                other.Move(-overlapX * pushClamped, 0.0f);
            } else {
                Move(-overlapX * (1.0f - pushClamped), 0.0f);
                other.Move(overlapX * pushClamped, 0.0f);
            }
        } else {
            // Resolve Y-axis
            if (deltaY > 0.0f) {
                Move(0.0f, overlapY * (1.0f - pushClamped));
                other.Move(0.0f, -overlapY * pushClamped);
            } else {
                Move(0.0f, -overlapY * (1.0f - pushClamped));
                other.Move(0.0f, overlapY * pushClamped);
            }
        }

        return true;

    }
    return false;
}

