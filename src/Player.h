//
// Created by Nathan Teh on 4/20/25.
//

#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "Animation.h"
#include <SFML/Audio.hpp>
#include "Camera.h"

extern Camera camera;

class Player : public GameObject {
public:
    Player(sf::Texture *texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f pos, float speed,
           float jumpHeight, sf::Vector2f size, sf::Vector2f collisionSize);
    ~Player() {}
    sf::Vector2f GetPosition() const override {return pos;}
    void Update(float deltaTime, float& playerY);
    void Draw(sf::RenderWindow& window) override;
    void OnCollision(sf::Vector2f direction);
    Collider* GetCollider() override {return new Collider(collisionBox);}
    bool IsPlatform() const override { return false; }
    float getPosY() {return pos.y;}


private:
    sf::RectangleShape mBody;
    Animation animation;
    float mSpeed;
    sf::Vector2f pos;
    bool canJump;
    float jumpHeight;
    sf::Vector2f velocity;
    bool isGrounded;
    unsigned int row;
    bool faceRight;
    sf::RectangleShape collisionBox;
    sf::Music jump;
    sf::Music victoryMusic;
    bool playedVictory = false;
};



#endif //PLAYER_H
