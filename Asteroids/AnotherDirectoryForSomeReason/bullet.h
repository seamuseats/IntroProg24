#pragma once

#include "graphics.h"

using namespace mssm;

class Bullet{
    public:
    Vec2d pos;
    double rot;
    bool checkCollision(Vec2d obj);
    void draw(Graphics& g);
};