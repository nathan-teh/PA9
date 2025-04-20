//
// Created by Nathan Teh on 4/19/25.
//
#pragma once
#include <SFML/Graphics.hpp>
#ifndef GAME_H
#define GAME_H



void Begin(const sf::Window& window);

void Update(float deltaTime);

void Render(sf::RenderWindow& window);

void MoveX(float x);
void MoveY(float y);


#endif //GAME_H
