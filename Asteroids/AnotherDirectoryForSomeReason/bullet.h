#pragma once

#include "graphics.h"

using namespace mssm;

class Bullet{
    public:
    Vec2d pos;
    Vec2d velocity;
    double rot;
    int life;
    bool checkCollision(Vec2d obj);
    void draw(Graphics& g);
};