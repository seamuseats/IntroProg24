#pragma once

#include "graphics.h"
#include "rand.h"
#include "math.h"
#include "vec2d.h"
#include "ship.h"
#include "asteroid.h"
#include "bullet.h"
#include "paths.h"

double distance(Vec2d pos1, Vec2d pos2){
    return (pos1 - pos2).magnitude();
}