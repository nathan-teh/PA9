#pragma once
#include "Enemy.h"

class WalkingEnemy : public Enemy {
public:
    WalkingEnemy(float x, float y, float speed, float range);
    void update(float deltaTime) override;

private:
    float range;  // How far the enemy will walk before turning around
    bool movingRight;  // Direction flag
};