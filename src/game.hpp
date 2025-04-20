#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <filesystem>

#include "renderer.hpp"
#include "Resources.hpp"
#include "camera.hpp"
#include "Map.hpp"
#include "player.hpp"
#include "Physics.hpp"

extern Camera camera;

void begin(const sf::Window& window);

void update(float deltaTime);

void render(Renderer& renderer);

#endif