//
// Created by Nathan Teh on 4/19/25.
//

#include "Game.h"

sf::Vector2f pos(600,350);
sf::CircleShape circle(100.0f, 360u);

void Begin(const sf::Window& window) {
    circle.setOrigin(sf::Vector2f(circle.getRadius(), circle.getRadius()));
    circle.setPosition(pos);
    circle.setFillColor(sf::Color::Red);
}



void Render(sf::RenderWindow& window) {
    window.draw(circle);
}

void MoveX(const float x) {
    if (pos.x + x < circle.getRadius() || pos.x + x > 1280-circle.getRadius()) return;
    pos.x += x;
    circle.setPosition(pos);
}

void MoveY(const float y) {
    if (pos.y + y < circle.getRadius() || pos.y + y > 720-circle.getRadius()) return;
    pos.y += y;
    circle.setPosition(pos);
}