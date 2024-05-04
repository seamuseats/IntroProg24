#include "world.h"

using namespace mssm; // namespace mssm

void World::draw(Graphics& g){
    for (int i = 0; i < wallPoints.size(); i++){
        if(i % 2 == 0){
            g.line(wallPoints[i], wallPoints[i + 1], WHITE);
        }
    }
}