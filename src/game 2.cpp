#include "game.hpp"

Map map(2.0);
Camera camera(20.0);
Player pirate;

sf::Texture texture("/Users/karentinoco/Documents/vsCode/2025Apps/PirateJump/images/duck.PNG");


void begin(const sf::Window &window) {
    Physics::init();

    sf::Image image("/Users/karentinoco/Documents/vsCode/2025Apps/PirateJump/images/mapo.png");
    pirate.position = map.CreateFromImage(image);
    pirate.begin();
}

void update(float deltaTime) { 
    Physics::update(deltaTime);
   pirate.Update(deltaTime);
    camera.position = pirate.position;

}

void render(Renderer& renderer) {
    map.Draw(renderer);
    pirate.Draw(renderer);
}
