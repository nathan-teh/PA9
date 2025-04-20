#include "Physics.hpp"


b2WorldId Physics::world = []() {
    b2WorldDef worldDef = b2DefaultWorldDef();       // Create local world def
    worldDef.gravity = (b2Vec2){0.0f, 9.2f};          // Set gravity
    return b2CreateWorld(&worldDef);                // Return the created world
}();



void Physics::init() {

}

void Physics::update(float deltaTime) {
   b2World_Step(Physics::world, deltaTime, 4);
}
