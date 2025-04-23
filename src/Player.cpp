//
// Created by Nathan Teh on 4/20/25.
//

#include "Player.h"

#include <iostream>

Camera camera(1000);

Player::Player(const sf::Texture* texture, const sf::Vector2f pos, float speed, float jumpHeight) : pos(pos) {
    this->mSpeed = speed;
    this->jumpHeight = jumpHeight;
    this->canJump = true;
    this->mBody.setSize((sf::Vector2f(52.0f * 0.9, 100.0f * 0.9)));
    this->mBody.setOrigin(sf::Vector2f((52.0 * 0.9f) / 2, (100.0f * 0.9) / 2));
    this->mBody.setTexture(texture);
    this->mBody.setPosition(pos);
    if (!jump.openFromFile("assets/sounds/Jump.ogg")) {
        std::cerr << "Failed to load jump sound!" << std::endl;
    }
}

Player::~Player() {
}

void Player::Update(float deltaTime) {
    velocity.x = 0.3f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) velocity.x -= mSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) velocity.x += mSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && canJump)
    {
        canJump = false;
        jump.play();
        velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight);
    }
    velocity.y += 981.0f * deltaTime;
    mBody.move(velocity * deltaTime);

    std::cout << mBody.getPosition().x << " " << mBody.getPosition().y << std::endl;

    camera.position.y = mBody.getPosition().y - 250.0f;


    // don't move camera, if player hits certain y change to that y section
    // add camera and position adjuster when you change the screen size

}

void Player::Draw(sf::RenderWindow& window) {
    window.draw(mBody);
}
void Player::OnCollision(sf::Vector2f direction) {
    if (direction.x > 0.0f) velocity.x = 0.0f;
    else if (direction.x < 0.0f) velocity.x = 0.0f;
    if (direction.y < 0.0f) {
        velocity.y = 0.0f;
        canJump = true;
    }
    else if (direction.y > 0.0f) velocity.y = 0.0f;


}