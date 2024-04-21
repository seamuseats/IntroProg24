#ifndef ASTEROID_H
#define ASTEROID_H
#include "vec2d.h"
#include "graphics.h"
#include "math.h"

using namespace mssm;

class Asteroid{
    public:
    Vec2d pos;
    Vec2d velocity;
    Vec2d pushPull;
    int size{60};
    void draw(Graphics& g);
};

#endif //ASTEROID_H