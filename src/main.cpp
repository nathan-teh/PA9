#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Character.h"
#include "Player.h"
#include <iostream>
#include <vector>
#include "Platform.h"
#include "Collider.h"
#include "Camera.h"

#include "Map.h"



int main()
{
    Map mapp;
    auto window = sf::RenderWindow(sf::VideoMode({1280u, 720u}), "CMake SFML Project");
    window.setFramerateLimit(60);
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("assets/images/Goose_v2.PNG")) {
        std::cerr << "Failed to load player texture!\n";
        return -1; // or handle error appropriately
    }    sf::Clock deltaClock;
    sf::Vector2f pos(250,600);

   // camera.position = pos;//sf::Vector2f({400,800});


    //std::vector<Platform*> platforms; // vector of Platform pointers


    sf::Texture brickTexture;
    if (!brickTexture.loadFromFile("assets/images/BlueBrick.png")) {
        std::cerr << "Failed to load brick texture!" << std::endl;
        return -1;
    }
    std::vector<std::unique_ptr<Platform>> platforms;
    Map map(75.f);
    map.loadMap(platforms, brickTexture);


    //Platform platform1(nullptr,sf::Vector2f(400.0f,200.0f),(sf::Vector2f(640.0f,500)));
   // Platform platform2(nullptr,sf::Vector2f(400.0f,100.0f),(sf::Vector2f(250.0f,400)));

    //platforms.push_back(&platform1);
    //platforms.push_back(&platform2);
    Player user(&playerTexture, pos, 100,100);
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
        sf::Vector2f direction;

        for (auto& platform : platforms) {
            if (platform->GetCollider()->checkCollision(*user.GetCollider(),direction,1.0f))
                user.OnCollision(direction);

        }

        window.clear();
        window.setView(camera.GetView(window.getSize()));
        user.Draw(window);
        for (auto& platform : platforms) {
            platform->Draw(window);
        }
        window.display();
    }
}