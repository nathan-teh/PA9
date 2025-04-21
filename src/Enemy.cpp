#include "Enemy.h"

Enemy::Enemy(float x, float y, float speed, const sf::Texture& texture)
    : position(x, y), speed(speed) {
    // Initialize sprite with texture
    sprite.setTexture(texture);
    sprite.setPosition(position);
}

void Enemy::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Enemy::getBounds() const {
    return sprite.getGlobalBounds();
}
