//
// Created by Nathan Teh on 4/20/25.
//

#ifndef PLATFORM_H
#define PLATFORM_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Platform : public GameObject{
public:
    Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f pos);
    ~Platform() {}
    void Update(float deltaTime, float& playerY) override {}
    bool IsPlatform() const override { return true; }
    void Draw(sf::RenderWindow& window) override;
    sf::Vector2f GetPosition() const override {return pos;}
    Collider* GetCollider() override {return new Collider(body);}
private:
    sf::RectangleShape body;
    sf::Vector2f pos;
};

#endif //PLATFORM_H