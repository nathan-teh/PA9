#include <SFML/Graphics.hpp>

#include "Player.h"
#include <iostream>
#include <vector>
#include "Platform.h"
#include "Collider.h"
#include "Camera.h"
#include "Button.hpp"
#include "Map.h"

/*
    Changes by Tifanie Ngo
    4/21: connected main menu, transition screen and added jump sound to gameplay code (based off secondBranch)
    4/22: pulled updatedMap, adjusted some values to make program functional, added victory sound, fixed bug
          where duck moves if user moves window for better visiblity

          - Added new main menu music after thinking about song choice; added gameplay music
*/

enum class GameState {
    MainMenu,
    TransitionScene,
    Gameplay
};

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
    sf::Texture titleTexture;
    if (!titleTexture.loadFromFile("assets/images/pirate-island-1.jpg")) {
        std::cerr << "Failed to load background image!\n";
        return -1;
    }
    sf::Music mainMenuMusic;
    if (!mainMenuMusic.openFromFile("assets/sounds/Main_Menu.ogg")) {
        std::cerr << "Failed to load music!\n";
        return -1;
    }
    Font mainMenuFont;
    if (!mainMenuFont.openFromFile("assets/images/TheRumIsGone-Wy1nG.ttf")) {
        std::cerr << "Failed to load font\n";
        return -1;
    }
    sf::Texture playerTexture2;

    if (!playerTexture2.loadFromFile("assets/images/Goose_v2.png")) {
        std::cerr << "Failed to load player texture!\n";
        return -1; // or handle error appropriately
    }
    if (!playerTexture.loadFromFile("assets/images/Duck_Sprite_Sheet.png")) {
        std::cerr << "Failed to load player texture!\n";
        return -1; // or handle error appropriately
    }
    sf::Vector2f collisionSize = {30.0f,100.0f};
    sf::Clock deltaClock;
    sf::Vector2f pos(600,300);
    //std::vector<GameObject*> objects;
    std::vector<std::unique_ptr<GameObject>> objects;

    sf::Vector2f size(96,100); //character size keep aspect ratio
    //objects.push_back(&platform1);
    //objects.push_back(&platform2);
    //objects.push_back(&platform3);

    //sf::Vector2f pos{}; // set this to   // GET IMAGE SIZE

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
    sf::Music gameplayMusic;
    if (!gameplayMusic.openFromFile("assets/sounds/Play_Music.ogg")) {
        std::cerr << "Failed to load gameplay music!" << std::endl;
    }

    //std::cout << "INITIAL " << pos.x << " " << pos.y << std::endl;




    std::vector<std::unique_ptr<Platform>> platforms;
    Map map(50.f);

    // pass in a vector instead!!
    map.loadMap(objects, brownBrick, brokenBrick, wood, greyBrick, emptyBrick, pos);
    //auto user = std::make_unique<Player>(&playerTexture, sf::Vector2u(4, 5), 0.1f,pos, 200,100, size, collisionSize); //can change jump height/speed


    //std::cout << "FOUND " << pos.x << " " << pos.y << std::endl;

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



    //Player user(&playerTexture, pos, 165            ,215);
    auto player = std::make_unique<Player>(&playerTexture, sf::Vector2u(4, 5), 0.1f,pos, 200,215, size, collisionSize);
    Player* user = player.get(); // safe reference
    objects.push_back(std::move(player));

    float deltaTime = 0.0f;




    mainMenuMusic.setVolume(20);
    mainMenuMusic.play();

    sf::Sprite duckSprite(playerTexture2);
    duckSprite.setScale(Vector2f(0.3f, 0.3f));
    duckSprite.setPosition(Vector2f(250.f, 250.f));

    sf::Sprite bgMainMenu(titleTexture);
    sf::Vector2f windowSize(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
    sf::Vector2f textureSize(static_cast<float>(titleTexture.getSize().x), static_cast<float>(titleTexture.getSize().y));
    bgMainMenu.setScale(Vector2f(windowSize.x / textureSize.x, windowSize.y / textureSize.y));

    sf::Text title(mainMenuFont);
    title.setCharacterSize(70);
    title.setFillColor(sf::Color::Cyan);
    title.setStyle(sf::Text::Italic);
    title.setString("YO-HO JUMP o");
    title.setPosition(Vector2f(580.0f, 300.0f));

    Button button(Vector2f(300.0f, 100.0f), Vector2f(750.0f, 445.0f), sf::Color(33, 122, 24));

    sf::Text buttonText(mainMenuFont);
    buttonText.setCharacterSize(70);
    buttonText.setFillColor(sf::Color::Black);
    buttonText.setString("PLAY");
    buttonText.setPosition(Vector2f(770.0f, 450.0f));

    // --- Set initial game state ---
    GameState currentState = GameState::MainMenu;
    sf::Clock transitionClock;
    bool transitionStarted = false;

    while (window.isOpen())
    {
        deltaTime = deltaClock.restart().asSeconds();

        // DO NOT REMOVE (fixes bug where duck moves when window moves)
        if (deltaTime > 0.05f) deltaTime = 0.05f;

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                mainMenuMusic.stop();
                gameplayMusic.stop();
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) window.close();
        }


        window.clear();

        camera.position.x = window.getSize().x / 1.8f;
        window.setView(window.getDefaultView());
        window.draw(elevation);


        // --- MAIN MENU ---
        if (currentState == GameState::MainMenu)
        {
            window.setView(window.getDefaultView());
            if (button.isMouseOverButton(window))
            {
                button.setFillColor(sf::Color(85, 245, 71));
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                {
                    button.setFillColor(sf::Color::Blue);
                    currentState = GameState::TransitionScene;  // Transition to next screen
                }
            }
            else button.setFillColor(sf::Color(33, 122, 24));

            window.draw(bgMainMenu);
            window.draw(duckSprite);
            window.draw(title);
            window.draw(button);
            window.draw(buttonText);
        }

        // --- TRANSITION SCENE ---
        else if (currentState == GameState::TransitionScene)
        {
            mainMenuMusic.stop();
            if (!transitionStarted) {
                transitionClock.restart();
                transitionStarted = true;
            }

            window.setView(window.getDefaultView());

            window.clear(sf::Color::Black);

            sf::Text transitionText(mainMenuFont);
            transitionText.setString("I have to find my parrot...");
            transitionText.setCharacterSize(20);
            transitionText.setFillColor(sf::Color::White);
            transitionText.setPosition(Vector2f(480.0f, 330.0f));
            window.draw(transitionText);

            if (transitionClock.getElapsedTime().asSeconds() > 5.0f) currentState = GameState::Gameplay;
        }
        else if (currentState == GameState::Gameplay)
        {
            if (gameplayMusic.getStatus() != sf::Music::Status::Playing) gameplayMusic.play();
            //user->Update(deltaTime);
            sf::Vector2f direction;

            for (auto& obj : objects)
                obj->Update(deltaTime);

            for (const auto& obj : objects) {
                if (obj->IsPlatform()) {
                    if (obj->GetCollider()->checkCollision(*user->GetCollider(), direction, 1.0f))
                        user->OnCollision(direction);
                }
            }
            window.clear();
            window.setView(camera.GetView(window.getSize()));
            window.draw(backgroundSprite);


            for (auto& obj : objects)
                obj->Draw(window);
            user->Draw(window);

            window.setView(window.getDefaultView());
            //camera.position.x = window.getSize().x / 2;
            window.draw(elevation);
        }
        window.display();
    }
}