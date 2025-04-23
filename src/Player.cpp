//
// Created by Nathan Teh on 4/20/25.
//

#include "Player.h"

#include <iostream>

Camera camera(1000);
int currentZone = -1;

Player::Player(const sf::Texture* texture, const sf::Vector2f pos, float speed, float jumpHeight): pos(pos) {
    this->mSpeed=speed;
    this->jumpHeight=jumpHeight;
    this->canJump=true;
    this->mBody.setSize((sf::Vector2f(52.0f * 0.9, 100.0f * 0.9)));
    this->mBody.setOrigin(sf::Vector2f((52.0 * 0.9f)/2, (100.0f*0.9)/2));
    this->mBody.setTexture(texture);
    this->mBody.setPosition(pos);

}

Player::~Player() {
}

void Player::Update(float deltaTime, float& playerY){
    velocity.x=0.3f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) velocity.x-=mSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) velocity.x+=mSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && canJump)
    {
        canJump=false;
        velocity.y=-sqrtf(2.0f*981.0f*jumpHeight);
    }
    velocity.y+=981.0f*deltaTime;
    mBody.move(velocity*deltaTime);

    //std::cout << mBody.getPosition().x << " " << mBody.getPosition().y << std::endl;
    std::cout << "camera: " << camera.position.y << std::endl;

    // if (mBody.getPosition().y) {
    //
    //
    //
    // }

    // if (mBody.getPosition().y < 9445) {
    //     camera.position.y = 9430;
    // } else {
        camera.position.y = mBody.getPosition().y -325.0f;
    // }

    // if (camera.position.y < )
    //
    // else if (camera.position.y < 9430) {
    //     camera.position.y = 9425;
    // }

    // if (mBody.getPosition().y < 4130) {
    //     //camera.position.y = mBody.getPosition().y -325.0f;
    // } else if (camera.position.y < 4980) {
    //     camera.position.y = 4975;
    // } else if (camera.position.y < 5830) {
    //     camera.position.y = 5825;
    // } else if (camera.position.y < 6630) {
    //     camera.position.y = 6625;
    // } else if (camera.position.y < 7680) {
    //     camera.position.y = 4975;
    // } else if (camera.position.y < 8580) {
    //     camera.position.y = 8575;
    // } else if (camera.position.y < 9430) {
    //     camera.position.y = 9425;
    // } else {
    //     camera.position.y = mBody.getPosition().y -325.0f;
    // }

    //const float screenHeight = 200.0f;

    //std::cout << camera.position.x << " " << camera.position.y << std::endl;

    playerY=mBody.getPosition().y;

    // Get the Y coordinate of the player
    // float pY = this->pos.y;
    //
    // // Determine what vertical "zone" they’re in
    // int newZone = static_cast<int>(pY / screenHeight);
    //
    // if (newZone != currentZone) {
    //     currentZone = newZone;
    //
    //     // Lock the camera to this vertical zone
    //     float camY =( (currentZone + 0.5f) * screenHeight) -310;
    //     camera.position.y = camY;
    // }


    // don't move camera, if player hits certain y change to that y section
    // add camera and position adjuster when you change the screen size

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