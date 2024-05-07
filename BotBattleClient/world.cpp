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
        for (int i = 0; i < GridCenters.size(); i++){
            g.ellipse(GridCenters[i] + viewTransform, 100, 100, TPGREEN, TPGREEN);
            if(GridCenters.size() >= 2 && i + 1 < GridCenters.size()){
                g.line(GridCenters[i] + viewTransform, GridCenters[i + 1] + viewTransform, TPGREEN);
            }
        }
    }
}

void World::clean(){
    for(int i = 0; i < wallPoints.size(); i++){
        for(int a = 0; a < wallPoints.size(); a++){
            if(a != i){
                if((wallPoints[i] - wallPoints[a]).magnitude() <= 0.01){
                    if(i < 0){
                        wallPoints.removeAtIndex(i);
                        wallAngles.removeAtIndex(i);
                        a--;
                        i--;
                    }
                    else{
                        wallPoints.removeAtIndex(a);
                        wallAngles.removeAtIndex(a);
                        a--;
                        i--;
                    }
                }
            }
        }
    }
    if(GridCenters.size() > (4 * 5)){
        for(int i = 0; i < GridCenters.size(); i++){
            GridCenters.removeAtIndex(i);
            i--;
        }
    }
}
