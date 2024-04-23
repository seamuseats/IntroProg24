#pragma once
#include "vec2d.h"
#include "graphics.h"
#include "math.h"

using namespace mssm;

class Ship{
    public:
    Vec2d pos;
    Vec2d velocity;
    Vec2d accel;
    double rot;
    int size{25};
    void draw(Graphics& g);
};
