//
// Created by Nathan Teh on 4/20/25.
//

#include "Player.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <iostream>

// Global camera object
Camera camera(1000);

// Constructor
Player::Player(const sf::Texture* texture, const sf::Vector2f pos, float speed, float jumpHeight) : pos(pos) {
    this->mSpeed = speed;
    this->jumpHeight = jumpHeight;
    this->canJump = true;

    this->mBody.setSize(sf::Vector2f(52.0f * 0.9f, 100.0f * 0.9f));
    this->mBody.setOrigin(sf::Vector2f((52.0f * 0.9f) / 2.0f, (100.0f * 0.9f) / 2.0f));
    this->mBody.setTexture(texture);
    this->mBody.setPosition(pos);

}

// Destructor
Player::~Player() {
}

// Update game logic and animation
void Player::Update(float deltaTime, float& playerY) {
    velocity.x = 0.3f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) velocity.x -= mSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) velocity.x += mSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && canJump) {
        canJump = false;
        velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight);
    }

    velocity.y += 981.0f * deltaTime;
    mBody.move(velocity * deltaTime);

    std::cout << mBody.getPosition().x << " " << mBody.getPosition().y << std::endl;

    camera.position.y = mBody.getPosition().y - 250.0f;
    playerY = mBody.getPosition().y;

}

// Draw player on window
void Player::Draw(sf::RenderWindow& window) {
    window.draw(mBody);
}

// Handle collision directionally
void Player::OnCollision(sf::Vector2f direction) {
    if (direction.x != 0.0f) velocity.x = 0.0f;

    if (direction.y < 0.0f) {
        velocity.y = 0.0f;
        canJump = true;
    }
    else if (direction.y > 0.0f) {
        velocity.y = 0.0f;
    }
}
