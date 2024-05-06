#pragma once

#include "botmanager.h"

class World{
    public:
    Array<Vec2d> wallPoints;
    Array<double> wallAngles;
    void draw(mssm::Graphics& g);
};