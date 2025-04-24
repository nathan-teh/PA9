///////////////////////////////////////////////////////////////////////////////
/// \file         Animation.cpp
/// \author       Nathan Teh
/// \date         4/20/25
/// \brief        This file sets up the animation for Yo-Ho Jump! Manages sprite
///               sheet animation frames and directional flipping.
///////////////////////////////////////////////////////////////////////////////

#include "Animation.h"

///////////////////////////////////////////////////////////////////////
/// Animation(sf::Texture *texture, sf::Vector2u imageCount, float switchTime)
/// \pre     texture must be loaded and valid
/// \post    initializes frame size, switch timing, and sets the current frame to (0, 0)
/// \param   texture (pointer to the sprite sheet texture); imageCount (# of images in 
///              the texture (columns x rows); switchTime (time between animation frame changes 
///              (in seconds)
/// \return  none
/// \throw   none
///////////////////////////////////////////////////////////////////////
Animation::Animation(sf::Texture *texture, sf::Vector2u imageCount, float switchTime) {
    this->imageCount=imageCount;
    this->switchTime=switchTime;
    this->totalTime=0.0f;
    this->currentImage.x=0;

    // calculate individual frame size from full texture
    this->uvRect.size.x=texture->getSize().x/imageCount.x;
    this->uvRect.size.y=texture->getSize().y/imageCount.y;
}

///////////////////////////////////////////////////////////////////////
/// Animation::Update(int row, float deltaTime, bool faceRight)
/// \pre     animation initialized with a valid texture and frame layout
/// \post    advances  animation frame if enough time has passed; updates
///          the UV rectangle to reflect  current frame / direction
/// \param   row (row of sprite sheet to animate); deltaTime (time in seconds 
///              since recent frame update); faceRight (determines direction
///              sprite faces)
/// \return  none
/// \throw   none
///////////////////////////////////////////////////////////////////////
void Animation::Update(int row, float deltaTime, bool faceRight) {
    currentImage.y=row; // set animation row
    totalTime+=deltaTime; // accumulate time

    // if enough time has passed
    if (totalTime>=switchTime) {
        currentImage.x++;
        totalTime-=switchTime;

        //loop animation horizontally
        if (currentImage.x>=imageCount.x) currentImage.x=0;
    }

    // set vertical frame position
    uvRect.position.y=currentImage.y*uvRect.size.y;

    // horizontal flipping logic
    if (!faceRight) {
        // left-facing (normal direction)
        uvRect.position.x=currentImage.x*uvRect.size.x;
        uvRect.size.x=abs(uvRect.size.x);
    }
    else {
        // right-facing (flip horizontally using negative width)
        uvRect.position.x=(currentImage.x + 1)* abs(uvRect.size.x);
        uvRect.size.x=-abs(uvRect.size.x);
    }
}

