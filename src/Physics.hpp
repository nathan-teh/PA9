#ifndef PHYSICS
#define PHYSICS

#include <box2d/box2d.h>


class Physics {
public:
   static void init();
   static void update(float deltaTime);
   static b2WorldId world;
};

#endif