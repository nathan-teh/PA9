#pragma once
#include <SFML/Graphics.hpp>

class Enemy {
public:
    Enemy(float x, float y, float speed, const sf::Texture& texture);
    virtual ~Enemy() = default;

    virtual void update(float deltaTime) = 0;  // Pure virtual function for AI
    void draw(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;

protected:
    sf::Sprite sprite;
    float speed;
    sf::Vector2f position;
};
