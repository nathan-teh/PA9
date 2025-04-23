//
// Created by Nathan Teh on 4/20/25.
//

#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "Camera.h"

extern Camera camera;

class Player : public Character {
public:
    Player(const sf::Texture* texture, sf::Vector2f pos, float speed, float jumpHeight);
    ~Player();


    void Update(float deltaTime, float& playerY) override;
    void Draw(sf::RenderWindow& window) override;
    void OnCollision(sf::Vector2f direction);
    Collider* GetCollider(){return new Collider(mBody);}
    sf::Vector2f pos;

private:

    sf::RectangleShape mBody;
    float mSpeed;

    bool canJump;
    float jumpHeight;
    sf::Vector2f velocity;
};




#endif //PLAYER_H
