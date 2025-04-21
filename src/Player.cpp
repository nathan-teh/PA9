//
// Created by Nathan Teh on 4/20/25.
//

#include "Player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f pos, float speed,
           float jumpHeight, sf::Vector2f size) : animation(texture, imageCount, switchTime) {

    this->mSpeed=speed;
    this->jumpHeight=jumpHeight;
    this->canJump=true;
    this->mBody.setSize(size);
    this->mBody.setOrigin((size)/2.0f);
    this->mBody.setTexture(texture);
    this->mBody.setPosition(pos);
    isGrounded=false;
    row=3;

}

void Player::Update(float deltaTime){
    velocity.x=0.0f;
    isGrounded = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) velocity.x-=mSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) velocity.x+=mSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && canJump)
    {
        canJump=false;
        velocity.y=-sqrtf(2.0f*981.0f*jumpHeight);
    }
    if (velocity.x==0.0f) row=3;
    else {
        if (velocity.x>0.0f) row=2;
        else row=1;
    }
    velocity.y+=981.0f*deltaTime;
    mBody.move(velocity*deltaTime);

    if (!isGrounded) canJump = false;
    animation.Update(row, deltaTime);
    mBody.setTextureRect(animation.uvRect);
}

void Player::Draw(sf::RenderWindow &window) {
    window.draw(mBody);
}
void Player::OnCollision(sf::Vector2f direction) {
    if (direction.x>0.0f || direction.x<0.0f) velocity.x=0.0f;
    if (direction.y<0.0f) {
        velocity.y=0.0f;
        canJump=true;
        isGrounded = true;

    }
    else if (direction.y>0.0f) velocity.y=0.0f;
}