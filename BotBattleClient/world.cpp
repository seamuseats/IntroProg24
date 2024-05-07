#include "world.h"

using namespace mssm; // namespace mssm

void World::draw(Graphics& g, Vec2d viewTransform){
    for (int i = 0; i < wallPoints.size(); i++){
        int confidence;
        if(i < 4){
            confidence = 50;
        }
        else{
            confidence = 100;
        }
        Vec2d pos1 = wallPoints[i] + Vec2d(confidence, 0).rotated(wallAngles[i]);
        Vec2d pos2 = wallPoints[i] + Vec2d(-confidence, 0).rotated(wallAngles[i]);
        g.line(pos1 + viewTransform, pos2 + viewTransform, RED);
    }
}
