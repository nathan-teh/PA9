//
// Created by Nathan Teh on 4/20/25.
//

#include "Player.h"

Camera camera(1200);

Player::Player(const sf::Texture* texture, const sf::Vector2f pos, float speed, float jumpHeight): pos(pos) {
    this->mSpeed=speed;
    this->jumpHeight=jumpHeight;
    this->canJump=true;
    this->mBody.setSize((sf::Vector2f(80.0f, 100.0f)));
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
        velocity.y=-sqrtf(2.0f*981.0f*jumpHeight);
    }
    velocity.y+=981.0f*deltaTime;
    mBody.move(velocity*deltaTime);
    camera.position = pos;

}

void Player::Draw(sf::RenderWindow &window) {
    window.draw(mBody);
}
void Player::OnCollision(sf::Vector2f direction) {
    if (direction.x>0.0f) velocity.x=0.0f;
    else if (direction.x<0.0f) velocity.x=0.0f;
    if (direction.y<0.0f) {
        velocity.y=0.0f;
        canJump=true;
    }
    else if (direction.y>0.0f) velocity.y=0.0f;


}