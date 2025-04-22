#include <SFML/Graphics.hpp>

#include "Player.h"
#include <iostream>
#include <vector>

#include "Animation.h"
#include "Platform.h"
#include "Collider.h"
#include "Camera.h"

#include "Map.h"


int main()
{
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

    if (!playerTexture.loadFromFile("assets/images/Duck_Sprite_Sheet.png")) {
        std::cerr << "Failed to load player texture!\n";
        return -1; // or handle error appropriately
    }
    sf::Vector2f collisionSize = {30.0f,80.0f};
    sf::Clock deltaClock;
    sf::Vector2f pos(600,300);
    std::vector<GameObject*> objects;
    Platform platform1(nullptr,sf::Vector2f(400.0f,200.0f),(sf::Vector2f(640.0f,500)));
    Platform platform2(nullptr,sf::Vector2f(400.0f,100.0f),(sf::Vector2f(250.0f,400)));
    Platform platform3(nullptr,sf::Vector2f(400.0f,400.0f),(sf::Vector2f(800.0f,500)));

    sf::Vector2f size(96,100); //character size keep aspect ratio
    //objects.push_back(&platform1);
    //objects.push_back(&platform2);
    //objects.push_back(&platform3);
    }

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
    map.loadMap(objects, brownBrick, brokenBrick, wood, greyBrick, emptyBrick, pos);
    Player user(&playerTexture, sf::Vector2u(4, 5), 0.1f,pos, 200,100, size, collisionSize); //can change jump height/speed


    std::cout << "FOUND " << pos.x << " " << pos.y << std::endl;

    //pos.y = pos.y + 50.f;

    //Platform platform1(nullptr,sf::Vector2f(400.0f,200.0f),(sf::Vector2f(640.0f,500)));
   // Platform platform2(nullptr,sf::Vector2f(400.0f,100.0f),(sf::Vector2f(250.0f,400)));

    //platforms.push_back(&platform1);
    //platforms.push_back(&platform2);

    sf::Font font("assets/images/Jersey15-Regular.ttf");
    sf::Text elevation(font);
    elevation.setString("Elevation: ");
    elevation.setCharacterSize(30);
    elevation.setFillColor(sf::Color::White);
    elevation.setPosition({50, 50});
        //{window.getSize().x / 10.0f, window.getSize().y / 10.0f});



    Player user(&playerTexture, pos, 165            ,215);
    Begin(window);
    objects.push_back(&user);

    float deltaTime = 0.0f;
    sf::Clock clock;
    while (window.isOpen())
    {
        deltaTime = deltaClock.restart().asSeconds();
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
        window.setView(camera.GetView(window.getSize()));
        window.draw(backgroundSprite);




        camera.position.x = window.getSize().x / 2.0f;
        user.Draw(window);
        window.setView(window.getDefaultView());
        window.draw(elevation);

        for (auto& obj : objects) //renders all objects
            obj->Draw(window);
        window.display();
    }
}
