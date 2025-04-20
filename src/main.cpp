#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Character.h"
#include "Player.h"
#include <iostream>
#include <vector>
#include "Platform.h"
#include "Collider.h"


int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1280u, 720u}), "CMake SFML Project");
    window.setFramerateLimit(60);
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("assets/images/Goose_v2.PNG")) {
        std::cerr << "Failed to load player texture!\n";
        return -1; // or handle error appropriately
    }    sf::Clock deltaClock;
    sf::Vector2f pos(600,300);
    std::vector<Platform*> platforms;
    Platform platform1(nullptr,sf::Vector2f(400.0f,200.0f),(sf::Vector2f(640.0f,500)));

    Player user(&playerTexture, pos, 100,50);
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
        user.Update(deltaTime);
        platform1.GetCollider()->checkCollision(*user.GetCollider(),1.0f);

        window.clear();
        user.Draw(window);
        platform1.Draw(window);

        window.display();
    }
}
