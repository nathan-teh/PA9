#include "player.hpp"

sf::Texture bird("/Users/karentinoco/Documents/vsCode/2025Apps/PirateJump/images/duck.PNG");

void Player::begin(){
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = (b2Vec2){position.x, position.y};

    this->body = b2CreateBody(Physics::world, &bodyDef); // ah i dont know man!!

    b2Polygon dynamicBox = b2MakeBox(1.0F, 1.0F);
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0F;
    shapeDef.material.friction = 0.3F;
    b2CreatePolygonShape(this->body, &shapeDef, &dynamicBox);
    
}


void Player::Update(float deltaTime) {
    float move = movementSpeed;


    b2Transform transform = b2Body_GetTransform(this->body);
    float radians = atan2(transform.q.s, transform.q.c);
    position = sf::Vector2f({transform.p.y, transform.p.y});
    angle = radians * (180.0F / PI);

}

void Player::Draw(Renderer &renderer) {
    renderer.draw(bird, position, {2.0F, 2.0F}, angle);
}
