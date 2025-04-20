#ifndef RENDERER
#define RENDERER

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>

class Renderer {
    public:
        Renderer(sf::RenderTarget& target);
        void draw(const sf::Texture& texture, const sf::Vector2f& postion,
                    const sf::Vector2f& size, float angle = 0.0F);

    private:
    sf::RenderTarget& target;
};

#endif