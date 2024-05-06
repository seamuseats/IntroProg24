#include "world.h"

using namespace mssm; // namespace mssm

void World::draw(Graphics& g){
    for (int i = 0; i < wallPoints.size(); i++){
        Vec2d pos1 = wallPoints[i] + Vec2d(50, 0).rotated(wallAngles[i]);
        Vec2d pos2 = wallPoints[i] + Vec2d(-50, 0).rotated(wallAngles[i]);
        g.line(pos1 + Vec2d(g.width() / 2, g.height() / 2), pos2 + Vec2d(g.width() / 2, g.height() / 2), RED);
    }
}