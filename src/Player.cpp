//
// Created by Nathan Teh on 4/20/25.
//

#include "Player.h"

Player::Player(const sf::Texture* texture, const sf::Vector2f pos, float speed, float jumpHeight): pos(pos) {
    this->mSpeed=speed;
    this->jumpHeight=jumpHeight;
    this->canJump=true;
    this->mBody.setSize((sf::Vector2f(100.0f, 100.0f)));
    this->mBody.setOrigin(sf::Vector2f(100.0f, 100.0f)/2.0f);
    this->mBody.setTexture(texture);
    this->mBody.setPosition(pos);

}

Player::~Player() {
}

void Player::Update(float deltaTime){
    velocity.x=0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) velocity.x-=mSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) velocity.x+=mSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && canJump)
    {
        canJump=false;
        velocity.y=-sqrtf(2.0f*9.81f*jumpHeight);
    }
    velocity.y+=9.81f*deltaTime;
    mBody.move(velocity*deltaTime);
}

void Player::Draw(sf::RenderWindow &window) {
    window.draw(mBody);
}
