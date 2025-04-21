//
// Created by Nathan Teh on 4/20/25.
//

#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

class Player : public GameObject {
public:
    Player(const sf::Texture* texture, sf::Vector2f pos, float speed, float jumpHeight, sf::Vector2f size);
    ~Player() {}
    sf::Vector2f GetPosition() const override {return pos;}
    void Update(float deltaTime) override;
    void Draw(sf::RenderWindow& window) override;
    void OnCollision(sf::Vector2f direction);
    Collider* GetCollider() override {return new Collider(mBody);}
    bool IsPlatform() const override { return false; }


private:
    sf::RectangleShape mBody;
    float mSpeed;
    sf::Vector2f pos;
    bool canJump;
    float jumpHeight;
    sf::Vector2f velocity;
    bool isGrounded;
};



#endif //PLAYER_H
