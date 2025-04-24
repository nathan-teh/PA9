/////////////////////////////////////////////////////////////////////////////////
/// \file         Player.cpp
/// \author       Nathan Teh, Tifanie Ngo
/// \date         4/20/25
/// \brief        This file sets up the Player aspects (movement, size, position,
///               speed, jump height, etc.) for Yo-Ho Jump!
///////////////////////////////////////////////////////////////////////////////

#include "Player.h"
#include <iostream>

Camera camera(1000);

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f pos, float speed,
               float jumpHeight, sf::Vector2f size,sf::Vector2f collisionSize) : animation(texture, imageCount, switchTime),pos(pos) {

    this->mSpeed=speed;
    this->jumpHeight=jumpHeight;
    this->canJump=true;

    collisionBox.setSize(collisionSize);
    collisionBox.setOrigin((collisionSize)/2.0f);
    collisionBox.setPosition(pos);

    this->mBody.setSize(size);
    this->mBody.setOrigin((size)/2.0f);
    this->mBody.setTexture(texture);
    this->mBody.setPosition(pos);
    isGrounded=false;
    row=0;
    faceRight=true;
    if (!jump.openFromFile("assets/sounds/Sequence-01.ogg")) {
        std::cerr << "Failed to load jump sound!" << std::endl;
    }
    if (!victoryMusic.openFromFile("assets/sounds/Victory_SFX.ogg")) {
        std::cerr << "Failed to load victory music!" << std::endl;
    }
}

void Player::Update(float deltaTime){
    velocity.x=0.0f;
    isGrounded = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) velocity.x-=mSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) velocity.x+=mSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && canJump)
    {
        canJump=false;
        jump.play();
        velocity.y=-sqrtf(2.0f*981.0f*jumpHeight);
    }
    if (velocity.x==0.0f) row=0;
    else {
        row=3;
        if (velocity.x>0.0) faceRight=true;
        else faceRight=false;
    }
    if (velocity.y!=0) row=1;
    velocity.y+=981.0f*deltaTime;
    sf::Vector2f newPos = collisionBox.getPosition() + velocity * deltaTime;
    collisionBox.setPosition(newPos);
    mBody.setPosition(collisionBox.getPosition());
    this->pos=newPos;

    if (!isGrounded) canJump = false;
    animation.Update(row, deltaTime,faceRight);
    mBody.setTextureRect(animation.uvRect);

    if (mBody.getPosition().y > 9430) {
        camera.position.y = 9985;
    } else if (mBody.getPosition().y > 8575) {
        camera.position.y = 9085;
    } else if (mBody.getPosition().y > 7720) {
        camera.position.y = 8185;
    } else if (mBody.getPosition().y > 6865) {
        camera.position.y = 7285;
    } else if (mBody.getPosition().y > 5825) {
        camera.position.y = 6385;
    } else if (mBody.getPosition().y > 4980) {
        camera.position.y = 5485;
    } else if (mBody.getPosition().y > 4125) {
        camera.position.y = 4585;
    } else if (mBody.getPosition().y > 3270) {
        camera.position.y = 3685;
    } else if (mBody.getPosition().y > 2420) {
        camera.position.y = 2785;
    } else if (mBody.getPosition().y > 1873) {
        camera.position.y = 2450;
    } else if (mBody.getPosition().y > 1000) {
        camera.position.y = 1420;
    }

    if (mBody.getPosition().y <= 1790.0 && !playedVictory) {
        victoryMusic.play();
        playedVictory = true;
    }
    // don't move camera, if player hits certain y change to that y section
    // add camera and position adjuster when you change the screen size

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