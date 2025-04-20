#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>

#include "camera.hpp"
#include "renderer.hpp"
#include "game.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode({1200, 900}), "Testing");
    sf::Clock deltaClock;
    Renderer renderer(window);

    window.setFramerateLimit(60);
    begin(window);

    while (window.isOpen()) {
        float deltaTime = deltaClock.restart().asSeconds();

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) 
                window.close();
        }

        window.setView(camera.GetView(window.getSize()));
        update(deltaTime);

        window.clear();
        render(renderer);
        window.display();
    }
}

