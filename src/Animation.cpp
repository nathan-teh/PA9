//
// Created by Nathan Teh on 4/20/25.
//

#include "Animation.h"
#include <SFML/Graphics.hpp>

Animation::Animation(sf::Texture *texture, sf::Vector2u imageCount, float switchTime) {
    this->imageCount=imageCount;
    this->switchTime=switchTime;
    this->totalTime=0.0f;
    this->currentImage.x=0;
    this->uvRect.size.x=texture->getSize().x/imageCount.x;
    this->uvRect.size.y=texture->getSize().y/imageCount.y;
}

void Animation::Update(int row, float deltaTime, bool faceRight) {
    currentImage.y=row;
    totalTime+=deltaTime;
    if (totalTime>=switchTime) {
        currentImage.x++;
        totalTime-=switchTime;
        if (currentImage.x>=imageCount.x) currentImage.x=0;
    }
    uvRect.position.y=currentImage.y*uvRect.size.y;
    if (!faceRight) {
        uvRect.position.x=currentImage.x*uvRect.size.x;
        uvRect.size.x=abs(uvRect.size.x);
    }
    else {
        uvRect.position.x=(currentImage.x + 1)* abs(uvRect.size.x);
        uvRect.size.x=-abs(uvRect.size.x);
    }
}

