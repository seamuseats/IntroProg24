#pragma once

#include "botmanager.h"

class World{
    public:
    Array<Vec2d> wallPoints;
    void draw(mssm::Graphics& g);
};