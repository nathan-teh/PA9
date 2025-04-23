#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Character.h"
#include "Player.h"
#include <iostream>
#include <vector>
#include "Platform.h"
#include "Collider.h"
#include "Camera.h"
#include "Music.h"
#include "Map.h"



int main()
{

    // Create the music player
    MusicPlayer backgroundMusic;
    // Load the music file
    if (!backgroundMusic.load("assets/music/Play_Music.ogg")) {
        std::cerr << "Failed to load background music!" << std::endl;
    }
    // Set volume and play it (it will loop)
    backgroundMusic.setVolume(40.f);
    backgroundMusic.play();

    sf::Texture backgroundTexture; 
    if (!backgroundTexture.loadFromFile("assets/images/frame.png")) { 
        std::cerr << "Failed to load player texture!\n"; 
    }

    sf::Sprite backgroundSprite(backgroundTexture);

    float scaleX = (1450.0F) / backgroundTexture.getSize().x;
    float scaleY = 10450.0F / backgroundTexture.getSize().y;
    backgroundSprite.setScale(sf::Vector2f(scaleX, scaleY));



    Map mapp;
    auto window = sf::RenderWindow(sf::VideoMode({1280u, 720u}), "CMake SFML Project");
    window.setFramerateLimit(60);
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("assets/images/Goose_v2.PNG")) {
        std::cerr << "Failed to load player texture!\n";
        return -1; // or handle error appropriately
    }    sf::Clock deltaClock;
    sf::Vector2f pos{}; // set this to   // GET IMAGE SIZE

   // camera.position = pos;//sf::Vector2f({400,800});


    //std::vector<Platform*> platforms; // vector of Platform pointers


    sf::Texture brownBrick;
    if (!brownBrick.loadFromFile("assets/images/brownV3.png")) {
        std::cerr << "Failed to load brick texture!" << std::endl;
        return -1;
    }
    sf::Texture brokenBrick;
    if (!brokenBrick.loadFromFile("assets/images/bb4.png")) {
        std::cerr << "Failed to load brick texture!" << std::endl;
        return -1;
    }
    sf::Texture wood;
    if (!wood.loadFromFile("assets/images/woody.png")) {
        std::cerr << "Failed to load brick texture!" << std::endl;
        return -1;
    }
    sf::Texture greyBrick;
    if (!greyBrick.loadFromFile("assets/images/fullBrick.png")) {
        std::cerr << "Failed to load brick texture!" << std::endl;
        return -1;
    }
    sf::Texture emptyBrick;
    if (!emptyBrick.loadFromFile("assets/images/partialBrick.png")) {
        std::cerr << "Failed to load brick texture!" << std::endl;
        return -1;
    }

    std::cout << "INITIAL " << pos.x << " " << pos.y << std::endl;




    std::vector<std::unique_ptr<Platform>> platforms;
    Map map(50.f);

    // pass in a vector instead!!
    map.loadMap(platforms, brownBrick, brokenBrick, wood, greyBrick, emptyBrick, pos);


    std::cout << "FOUND " << pos.x << " " << pos.y << std::endl;

    //pos.y = pos.y + 50.f;

    //Platform platform1(nullptr,sf::Vector2f(400.0f,200.0f),(sf::Vector2f(640.0f,500)));
   // Platform platform2(nullptr,sf::Vector2f(400.0f,100.0f),(sf::Vector2f(250.0f,400)));

    //platforms.push_back(&platform1);
    //platforms.push_back(&platform2);
        //{window.getSize().x / 10.0f, window.getSize().y / 10.0f});

    //
    float playerY;

    Player user(&playerTexture, pos, 165            ,215);
    sf::Font font("assets/images/Jersey15-Regular.ttf");
    sf::Text elevation(font);
    elevation.setCharacterSize(30);
    elevation.setFillColor(sf::Color::White);
    elevation.setPosition({50, 50});
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
        user.Update(deltaTime, playerY);
        elevation.setString("Altitude: " + std::to_string(static_cast<int>(playerY)));
        sf::Vector2f direction;

        for (auto& platform : platforms) {
            if (platform->GetCollider()->checkCollision(*user.GetCollider(),direction,1.0f))
                user.OnCollision(direction);

        }


        window.clear();
        window.setView(camera.GetView(window.getSize()));
        window.draw(backgroundSprite);


        camera.position.x = window.getSize().x / 2.0f;
        user.Draw(window);
        for (auto& platform : platforms) {
            platform->Draw(window);
        }
        window.setView(window.getDefaultView());
        window.draw(elevation);
        window.display();
    }
}