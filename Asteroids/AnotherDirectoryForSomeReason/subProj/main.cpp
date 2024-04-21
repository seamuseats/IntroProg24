#include "graphics.h"

using namespace std;
using namespace mssm;



int main(int argc, char *argv[])
{
    Graphics g("Geometrical Cuh", 1920, 1080);
    float height = g.height() - 100;
    float jumpY = g.height()/99;
    Vec2d paddlePos{(g.width() / 2), (g.height() - 60)};
    Vec2d paddleScl{150, 50};
    Vec2d cubePos{100, 100};
    Vec2d cubeScl{100, 100};
    float G{9.8};
    //location of endpoints
    Array<Vec2d> vecPos{{g.width() / 2, (g.height() / 2) + 10}, {g.width() / 2, (g.height() / 2) - 15}};
    //velocity[0] is the larger pendulum.
    Array<Vec2d> velocity{{100, 100}, {1, 1}};
    float c = 2;
    int lives{3};
    while (g.draw()) {
        velocity[0].y += G;
        velocity[1].y += G;
        velocity[1].x += (vecPos[0].x - vecPos[1].x);
        velocity[0] = (velocity[0] * 10) / (velocity[0].magnitude());
        velocity[1] = (velocity[1] * 5) / (velocity[1]).magnitude();
        vecPos[0] = velocity[0];
        vecPos[1] = velocity[1];
        g.line({(g.width() / 2), (g.height() / 2)}, vecPos[0], WHITE);
        g.line({vecPos[0].x, vecPos[0].y}, vecPos[1], WHITE);
    }
}
