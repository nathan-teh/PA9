///////////////////////////////////////////////////////////////////////////////
/// \file         main.cpp
/// \author       Tifanie Ngo, Issac Bermudez, Nathan Teh, Karen Tinoco
/// \date         4/23/25
/// \brief        This overall program creates a game called Yo-Ho Jump! This
///               game is about a pirate duck, who is searching far across the
///               Seven Seas for his long-lost parrot! Jump to the top of the 
///               tower to find him...or will you?
///////////////////////////////////////////////////////////////////////////////

#include "Button.hpp"
#include "Camera.h"
#include "GameObject.h"
#include "Map.h"
#include "Music.h"
#include "Player.h"
#include "TestFunctions.h"
#include <iostream>
#include <vector>

enum class GameState {
    MainMenu,
    TransitionScene,
    Gameplay
};

int main()
{
    // tests all 5 test cases (see TestFunctions.cpp) and writes results to file
    runAllTestsToFile();

    // load background texture for game
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/images/finalFinalImage.PNG")) {
        std::cerr << "Failed to load player texture!\n";
    }

    // create a sprite for the background and scales to fit window
    sf::Sprite backgroundSprite(backgroundTexture);
    float scaleX = (1450.0F) / backgroundTexture.getSize().x;
    float scaleY = 10450.0F / backgroundTexture.getSize().y;
    backgroundSprite.setScale(sf::Vector2f(scaleX, scaleY));


    // initializes window and game elements
    Map mapp;
    auto window = sf::RenderWindow(sf::VideoMode({1280u, 720u}), "YO-HO JUMP");
    window.setFramerateLimit(60); // frame rate limited to 60 FPS
    
    // loads additional game assets (background image, music, player textures, etc.)
    sf::Texture playerTexture;
    sf::Texture titleTexture;
    if (!titleTexture.loadFromFile("assets/images/pirate-island-1.jpg")) {
        std::cerr << "Failed to load background image!\n";
        return -1;
    }

    // loads main menu & gameplay music
    MusicPlayer mainMenuMusic;
    if (!mainMenuMusic.load("assets/sounds/Main_Menu.ogg")) {
        std::cerr << "Failed to load main menu music!\n";
        return -1;
    }
    MusicPlayer gameplayMusic;
    if (!gameplayMusic.load("assets/sounds/Play_Music.ogg")) {
        std::cerr << "Failed to load gameplay music!\n";
        return -1;
    }

    // loads main menu font
    sf::Font mainMenuFont;
    if (!mainMenuFont.openFromFile("assets/images/TheRumIsGone-Wy1nG.ttf")) {
        std::cerr << "Failed to load font\n";
        return -1;
    }

    // loads player textures for different sprites
    sf::Texture playerTexture2;

    if (!playerTexture2.loadFromFile("assets/images/Goose_v2.png")) {
        std::cerr << "Failed to load player texture!\n";
        return -1; // or handle error appropriately
    }
    if (!playerTexture.loadFromFile("assets/images/Duck_Sprite_Sheet.png")) {
        std::cerr << "Failed to load player texture!\n";
        return -1; // or handle error appropriately
    }

    // sets up initial player collision size & position
    sf::Vector2f collisionSize = {30.0f,100.0f};
    sf::Clock deltaClock;
    sf::Vector2f pos(600,300);
    std::vector<std::unique_ptr<GameObject>> objects;

    sf::Vector2f size(96,100); //character size keep aspect ratio

    // loads different platform textures
    sf::Texture brownBrick;
    if (!brownBrick.loadFromFile("assets/images/firstBrick.png")) {
        std::cerr << "Failed to load brick texture!" << std::endl;
        return -1;
    }
    sf::Texture brokenBrick;
    if (!brokenBrick.loadFromFile("assets/images/secondBrick.png")) {
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

    // initializes map
    Map map(50.f);
    map.loadMap(objects, brownBrick, brokenBrick, wood, greyBrick, emptyBrick, pos);

    // intializes altitude text element
    sf::Font font("assets/images/Jersey15-Regular.ttf");
    sf::Text elevation(font);
    elevation.setString("Elevation: ");
    elevation.setCharacterSize(30);
    elevation.setFillColor(sf::Color::White);
    elevation.setPosition({50, 50});

    // creates player object and adds it to objects vector
    auto player = std::make_unique<Player>(&playerTexture, sf::Vector2u(4, 5), 0.1f,pos, 200,215, size, collisionSize);
    Player* user = player.get(); // safe reference
    objects.push_back(std::move(player));

    // initializes game clock and activates initial altitude
    float deltaTime = 0.0f;
    int startingAltitude = pos.y;

    // playing main menu music
    mainMenuMusic.setVolume(20);
    mainMenuMusic.play();
    
    // duck sprite for main menu screen
    sf::Sprite duckSprite(playerTexture2);
    duckSprite.setScale(sf::Vector2f(0.3f, 0.3f));
    duckSprite.setPosition(sf::Vector2f(250.f, 250.f));

    // background image for main menu
    sf::Sprite bgMainMenu(titleTexture);
    sf::Vector2f windowSize(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
    sf::Vector2f textureSize(static_cast<float>(titleTexture.getSize().x), static_cast<float>(titleTexture.getSize().y));
    bgMainMenu.setScale(sf::Vector2f(windowSize.x / textureSize.x, windowSize.y / textureSize.y));

    // title text for main menu
    sf::Text title(mainMenuFont);
    title.setCharacterSize(70);
    title.setFillColor(sf::Color::Cyan);
    title.setStyle(sf::Text::Italic);
    title.setString("YO-HO JUMP o");
    title.setPosition(sf::Vector2f(580.0f, 300.0f));

    // play button
    Button button(sf::Vector2f(300.0f, 100.0f), sf::Vector2f(750.0f, 445.0f), sf::Color(33, 122, 24));
    sf::Text buttonText(mainMenuFont);
    buttonText.setCharacterSize(70);
    buttonText.setFillColor(sf::Color::Black);
    buttonText.setString("PLAY");
    buttonText.setPosition(sf::Vector2f(770.0f, 450.0f));

    // Set initial game state (main menu)
    GameState currentState = GameState::MainMenu;
    sf::Clock transitionClock;
    bool transitionStarted = false;

    // main game loop
    while (window.isOpen())
    {
        deltaTime = deltaClock.restart().asSeconds();

        // limit deltaTime to avoid excessive frame updates (prevents duck from being moved when
        //    render window is moved by user)
        if (deltaTime > 0.05f) deltaTime = 0.05f;

        // event handling for window closure or key presses
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

        // clear window before new elements are aded
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
                button.setFillColor(sf::Color(85, 245, 71)); // change color on mouse hover
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                {
                    button.setFillColor(sf::Color::Blue); // color when play button is clicked
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
            mainMenuMusic.stop(); // stop main menu music

            // start transition
            if (!transitionStarted) 
            {
                transitionClock.restart();
                transitionStarted = true;
            }

            window.setView(window.getDefaultView());
            window.clear(sf::Color::Black); // clear screen for transition

            // displays transition text
            sf::Text transitionText(mainMenuFont);
            transitionText.setString("I have to find my parrot...");
            transitionText.setCharacterSize(20);
            transitionText.setFillColor(sf::Color::White);
            transitionText.setPosition(sf::Vector2f(480.0f, 330.0f));
            window.draw(transitionText);

            // 5 second wait before gameplay
            if (transitionClock.getElapsedTime().asSeconds() > 5.0f) currentState = GameState::Gameplay;
        }

        // -- GAMEPLAY --
        else if (currentState == GameState::Gameplay)
        {
            // play gameplay music
            if (gameplayMusic.getStatus() != sf::Music::Status::Playing) gameplayMusic.play();
            sf::Vector2f direction;

            // update all game objects (player, platforms)
            for (auto& obj : objects)
                obj->Update(deltaTime);

            // check for collisions between player and platforms
            for (const auto& obj : objects) {
                if (obj->IsPlatform()) {
                    if (obj->GetCollider()->checkCollision(*user->GetCollider(), direction, 1.0f))
                        user->OnCollision(direction);
                }
            }

            // clear window & draw gameplay elements
            window.clear();
            window.setView(camera.GetView(window.getSize())); // set camera view
            window.draw(backgroundSprite); // draw background

            // draw all objects and player
            for (auto& obj : objects)
                obj->Draw(window);
            user->Draw(window);
            camera.position.x = window.getSize().x / 2.0f; // update & display player's altitude
            window.setView(window.getDefaultView());
            int rawAltitude = static_cast<int>(startingAltitude - user->GetPosition().y);
            int realAltitude = std::max(0, rawAltitude);
            elevation.setString("Altitude: " + std::to_string(realAltitude));
            window.draw(elevation);
        }
        window.display();
    }
}