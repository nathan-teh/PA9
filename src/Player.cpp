/////////////////////////////////////////////////////////////////////////////////
/// \file         Player.cpp
/// \author       Nathan Teh, Tifanie Ngo
/// \date         4/20/25
/// \brief        This file sets up the Player aspects (movement, size, position,
///               speed, jump height, etc.) for Yo-Ho Jump!
///////////////////////////////////////////////////////////////////////////////

#include "Player.h"
#include <iostream>

Camera camera(1000); // global camera object for tracking player movement

///////////////////////////////////////////////////////////////////////
/// Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, 
// sf::Vector2f pos, float speed, float jumpHeight, sf::Vector2f size, 
// sf::Vector2f collisionSize)
/// \pre     none
/// \post    initializes player position, size, animation, movement, collision
///          box, loads jump and victory SFX 
/// \param texture         (pointer to the texture used for player animation)
/// \param imageCount      (# of animation frames (columns x rows))
/// \param switchTime      (time between frame switches)
/// \param pos             (initial position of the player)
/// \param speed           (horizontal movement speed)
/// \param jumpHeight      (height the player can jump)
/// \param size            (size of the player's visible body)
/// \param collisionSize   (size of the player's collision box)
/// \return  none
/// \throw   none
///////////////////////////////////////////////////////////////////////
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

///////////////////////////////////////////////////////////////////////
/// Update(float deltaTime)
/// \pre     none
/// \post    processes keyboard input for movement, applies gravity, 
///          updates collision box position, animation triggers, adjusts 
///          camera position based on player Y pos
/// \param deltaTime  (time elapsed since last frame)
/// \return  none
/// \throw   none
///////////////////////////////////////////////////////////////////////
void Player::Update(float deltaTime){
    velocity.x=0.0f;
    isGrounded = false;

    // movement input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) velocity.x-=mSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) velocity.x+=mSpeed;
   
    // jump input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && canJump)
    {
        canJump=false;
        jump.play();
        velocity.y=-sqrtf(2.0f*981.0f*jumpHeight);
    }

    // animation logic
    if (velocity.x==0.0f) row=0;
    else {
        row=3;
        if (velocity.x>0.0) faceRight=true;
        else faceRight=false;
    }
    if (velocity.y!=0) row=1;

    // gravity
    velocity.y+=981.0f*deltaTime;
    sf::Vector2f newPos = collisionBox.getPosition() + velocity * deltaTime;
    collisionBox.setPosition(newPos);
    mBody.setPosition(collisionBox.getPosition());
    this->pos=newPos;

    if (!isGrounded) canJump = false;
    
    // update animation & apply texture
    animation.Update(row, deltaTime,faceRight);
    mBody.setTextureRect(animation.uvRect);

    // camera y-position control based on player height
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

    // victory sound once reaching the top
    if (mBody.getPosition().y <= 1790.0 && !playedVictory) {
        victoryMusic.play();
        playedVictory = true;
    }
    // don't move camera, if player hits certain y change to that y section
    // add camera and position adjuster when you change the screen size
}

///////////////////////////////////////////////////////////////////////
/// Draw(sf::RenderWindow &window) 
/// \pre     none
/// \post    draws player sprite to window
/// \param   window  (reference to SFML render window)
/// \return  none
/// \throw   none
///////////////////////////////////////////////////////////////////////
void Player::Draw(sf::RenderWindow &window) {
    window.draw(mBody);
}

///////////////////////////////////////////////////////////////////////
/// OnCollision(sf::Vector2f direction)
/// \pre     none
/// \post    resolves collisions with platforms and walls (horizontal
///          movement on X collisions; resets vertical velocity and re-
///          activates jumping on Y-downward collisions); upward collisions
///          stop vertical motion (doesn't reset jump state)
/// \param   direction (normalized vector representing collision direction)
/// \return  none
/// \throw   none
///////////////////////////////////////////////////////////////////////
void Player::OnCollision(sf::Vector2f direction) {
    if (direction.x>0.0f || direction.x<0.0f) velocity.x=0.0f;
    if (direction.y<0.0f) {
        velocity.y=0.0f;
        canJump=true;
        isGrounded = true;
    }

    else if (direction.y>0.0f) velocity.y=0.0f;
}