#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1280u, 720u}), "CMake SFML Project");
    window.setFramerateLimit(60);

    sf::Clock deltaClock;

    Begin(window);
    while (window.isOpen())
    {
        float deltaTime = deltaClock.restart().asSeconds();
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) window.close();
        }
        window.clear();
        Render(window);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            MoveX(-10);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            MoveX(10);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            MoveY(10);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            MoveY(-10);
        }
        window.display();
    }
}
