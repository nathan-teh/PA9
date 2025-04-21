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
    std::vector<GameObject*> objects;
    Platform platform1(nullptr,sf::Vector2f(400.0f,200.0f),(sf::Vector2f(640.0f,500)));
    Platform platform2(nullptr,sf::Vector2f(400.0f,100.0f),(sf::Vector2f(250.0f,400)));
    sf::Vector2f size(52,100);
    objects.push_back(&platform1);
    objects.push_back(&platform2);
    Player user(&playerTexture, pos, 100,100,size);
    objects.push_back(&user);
    Begin(window);
    while (window.isOpen())
    {
        float deltaTime = deltaClock.restart().asSeconds();
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) window.close();
        }
        for (auto& obj : objects)
            obj->Update(deltaTime);
        sf::Vector2f direction;
        for (const auto& obj : objects) {
            if (obj->IsPlatform()) {
                if (obj->GetCollider()->checkCollision(*user.GetCollider(), direction, 1.0f))
                    user.OnCollision(direction);
            }
        }
        window.clear();
        for (auto& obj : objects)
            obj->Draw(window);
        window.display();
    }

}