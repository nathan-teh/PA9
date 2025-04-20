#ifndef PLAYER
#define PLAYER
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>
#include <box2d/box2d.h>

#include "renderer.hpp"
#include "Physics.hpp"

constexpr float PI = 22.0F / 7.0F;

const float movementSpeed = 3.0;

class Player {
public:
    void begin();

    void Update(float deltaTime);
    void Draw(Renderer& renderer);

    sf::Vector2f position {};
    float angle{};
private:
    b2BodyId body; // prolly not need to be pointer, (*shrug)


};

#endif
