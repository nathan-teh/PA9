//
// Created by Nathan Teh on 4/20/25.
//

#ifndef COLLIDER_H
#define COLLIDER_H
#include <SFML/Graphics.hpp>



class Collider {
public:
    Collider(sf::RectangleShape& body) : body(body) {};
    ~Collider() = default;
    void Move(float dx, float dy) {body.move(sf::Vector2f(dx, dy));}
    bool checkCollision(Collider& other, float push);
    sf::Vector2f GetPosition() {return body.getPosition();}
    sf::Vector2f GetHalfSize() {return body.getSize()/2.0f;}
private:
    sf::RectangleShape& body;
};



#endif //COLLIDER_H
