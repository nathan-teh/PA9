///////////////////////////////////////////////////////////////////////////////
/// \file         Platform.h
/// \author       Nathan Teh
/// \date         4/20/25
/// \brief        This file sets up the platforms (static GameObjects)
///               for Yo-Ho Jump!
///////////////////////////////////////////////////////////////////////////////

#ifndef PLATFORM_H
#define PLATFORM_H

#include "GameObject.h"

class Platform : public GameObject{
public:
    Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f pos); // Constructor
    ~Platform() {} // Destructor
    void Update(float deltaTime) override {} // empty update function
    bool IsPlatform() const override { return true; } // checks if object is platform
    void Draw(sf::RenderWindow& window) override; // renders platform to screen
    sf::Vector2f GetPosition() const override {return pos;} // gets position of the platform
    Collider* GetCollider() override {return new Collider(body);} // returns collider associated with a platform
private:
    sf::RectangleShape body; // SFML shape representing platform
    sf::Vector2f pos;        // position of platform
};

#endif //PLATFORM_H