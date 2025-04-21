#include "Enemy.h"

class JumpingEnemy : public Enemy {
public:
    JumpingEnemy(float x, float y, float speed, float jumpHeight);
    void update(float deltaTime) override;

private:
    float jumpHeight;
    float jumpSpeed;
    bool jumpingUp;
};