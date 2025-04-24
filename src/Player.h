/////////////////////////////////////////////////////////////////////////////////
/// \file         Player.h
/// \author       Nathan Teh, Tifanie Ngo
/// \date         4/20/25
/// \brief        This file sets up the Player aspects (movement, size, position,
///               speed, jump height, etc.) for Yo-Ho Jump!
///////////////////////////////////////////////////////////////////////////////

#ifndef PLAYER_H
#define PLAYER_H

#include "Animation.h"
#include "Camera.h"
#include "GameObject.h"
#include <SFML/Audio.hpp>

extern Camera camera;

class Player : public GameObject {
public:
    Player(sf::Texture *texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f pos, float speed,
           float jumpHeight, sf::Vector2f size, sf::Vector2f collisionSize); // Constructor
    ~Player() {} // Destructor
    /*
       * FOR NETWORKING (UNCOMMENT IF YOU WANT TO TEST IT, COMMENT THE DESTRUCTOR ABOVE)
       ~Player();
    */
    sf::Vector2f GetPosition() const override {return pos;}  // gets current player position
    void Update(float deltaTime) override; // updates movement, animation, camera
    void Draw(sf::RenderWindow& window) override; // renders player sprite
    void OnCollision(sf::Vector2f direction); // handles player collision response
    Collider* GetCollider() override {return new Collider(collisionBox);} // returns player collider
    bool IsPlatform() const override { return false; } // determines object as non-platform
    float getPosY() {return pos.y;} // gets current Y-position of player

private:
    sf::RectangleShape mBody; // visual render of player
    Animation animation; // handles sprite animation
    float mSpeed; // movement speed
    sf::Vector2f pos; // current position
    bool canJump; // flag for jump capability
    float jumpHeight; // jump height player is capable of
    sf::Vector2f velocity; // current velocity of player
    bool isGrounded; // flag for grounded state
    unsigned int row; // current animation row
    bool faceRight; // direction player is facing
    sf::RectangleShape collisionBox; // collision boundary
    sf::Music jump; // jump SFX
    sf::Music victoryMusic; // victory SFX
    bool playedVictory = false; // flag for victory SFX
};



#endif //PLAYER_H