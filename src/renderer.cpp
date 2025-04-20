#include "renderer.hpp"

Renderer::Renderer(sf::RenderTarget &target) : target(target){}

// added more code here
void Renderer::draw(const sf::Texture &texture, const sf::Vector2f &postion, const sf::Vector2f &size, float angle) {
    sf::Sprite sprite(texture);
    sprite.setTexture(texture, true);
    sprite.setOrigin((sf::Vector2f) texture.getSize() / 2.0F);
    sprite.setRotation(sf::degrees(angle));
    sprite.setPosition(postion);
    sprite.setScale({size.x / texture.getSize().x, size.y / texture.getSize().y});

    target.draw(sprite);
}