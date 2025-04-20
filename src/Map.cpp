#include "Map.hpp"

sf::Texture texture2("/Users/karentinoco/Documents/vsCode/2025Apps/PirateJump/images/BlueBrick.PNG");
Map::Map(float cellSize) : cellSize(cellSize), grid()
{
}

void Map::Draw(Renderer &renderer) {

    int x = 0;
    for (const auto& column : grid) {
        int y = 0;
        for (const auto& cell :  column) {
            if (cell) {
                renderer.draw(texture2, sf::Vector2f(cellSize * x + cellSize / 2.0, cellSize * y + cellSize / 2.0),
                sf::Vector2f(cellSize, cellSize));
            }
            y++;
        }
        x++;
    }
}

sf::Vector2f Map::CreateFromImage(const sf::Image &image) {

    grid = std::vector(image.getSize().x, std::vector(image.getSize().y, 0));

    sf::Vector2f playerPosition{};

    for (unsigned int x = 0; x < grid.size(); x++) {
        for (unsigned int y = 0; y < grid[x].size(); y++) {

            sf::Color color = image.getPixel({x,y});
            if (color == sf::Color::Black) {
                grid[x][y] = 1;

                // static box
                b2BodyDef bodyDef = b2DefaultBodyDef();
                bodyDef.type = b2_staticBody;
                bodyDef.position = (b2Vec2){static_cast<float>(cellSize * x + cellSize / 2.0),static_cast<float>(cellSize * y + cellSize / 2.0)};
                b2BodyId body = b2CreateBody(Physics::world, &bodyDef); // please be right, PRETTY PLEASE!!
                
                // polygon
                b2Polygon box = b2MakeBox(cellSize / 2.0F, cellSize / 2.0F);

                b2ShapeDef shapeDef = b2DefaultShapeDef();

                b2ShapeId shapeId = b2CreatePolygonShape(body, &shapeDef, &box);

            }
            else if (color == sf::Color::Red) {
                playerPosition = sf::Vector2f(cellSize * x + cellSize / 2.0, 
                                                 cellSize * y + cellSize / 2.0);

            }


        }
    }

    return playerPosition;
}
