#include "WalkingEnemy.hpp"

WalkingEnemy::WalkingEnemy(float x, float y, float speed, float range)
    : Enemy(x, y, speed), range(range), movingRight(true) {
    // Set a texture for the walking enemy sprite
    // Example: sprite.setTexture(texture);
}

void WalkingEnemy::update(float deltaTime) {
    // Move the enemy left or right
    if (movingRight) {
        position.x += speed * deltaTime;
        if (position.x >= range) {
            movingRight = false;  // Turn around when reaching the end of the range
        }
    }
    else {
        position.x -= speed * deltaTime;
        if (position.x <= 0) {
            movingRight = true;  // Turn around when reaching the start of the range
        }
    }
    sprite.setPosition(position);
}