#include "JumpingEnemy.hpp"

JumpingEnemy::JumpingEnemy(float x, float y, float speed, float jumpHeight)
    : Enemy(x, y, speed), jumpHeight(jumpHeight), jumpSpeed(0), jumpingUp(true) {
    // Set a texture for the jumping enemy sprite
    // Example: sprite.setTexture(texture);
}

void JumpingEnemy::update(float deltaTime) {
    if (jumpingUp) {
        jumpSpeed += 9.8f * deltaTime;  // Simulate gravity (basic physics)
        position.y -= jumpSpeed;
        if (position.y <= jumpHeight) {
            jumpingUp = false;  // Start falling after reaching peak height
        }
    }
    else {
        jumpSpeed -= 9.8f * deltaTime;  // Fall down
        position.y += jumpSpeed;
        if (position.y >= 0) {  // Ground level
            position.y = 0;
            jumpingUp = true;  // Start jumping again
        }
    }
    sprite.setPosition(position);
}