#pragma once

#include "botmanager.h"

class World{
    public:
    Array<Vec2d> wallPoints;
    Array<double> wallAngles;
    Array<Vec2d> GridCenters;
    void draw(mssm::Graphics& g, Vec2d viewTransform);
    void clean();
};