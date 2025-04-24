///////////////////////////////////////////////////////////////////////////////
/// \file         Animation.h
/// \author       Nathan Teh
/// \date         4/20/25
/// \brief        This file sets up the animation for Yo-Ho Jump! Manages sprite
///               sheet animation frames and directional flipping.
///////////////////////////////////////////////////////////////////////////////

#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

class Animation {
public:
    Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime); // Constructor
    ~Animation(){} // Destructor
    void Update(int row,float deltaTime, bool faceRight); // updates animation frame based on time & direction
    sf::IntRect uvRect; // UV rectangle of the texture portion to render
private:
    sf::Vector2u imageCount; // # of frames in the sprite sheet (columns x rows)
    sf::Vector2u currentImage; // current frame index (x: column/frame, y: row/animation state)
    float switchTime; // time interval between frame-switching
    float totalTime; // time accumulator used to determine frame-switching occurs
};

#endif //ANIMATION_H
