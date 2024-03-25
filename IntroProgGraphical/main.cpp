#include "graphics.h"
#include "rand.h"

using namespace std;
using namespace mssm;



int main(int argc, char *argv[])
{
    Graphics g("prong", 1024, 768);
    float height = g.height() - 100;
    float jumpY = g.height() / 99;
    Vec2d paddlePos{(g.width() / 2), (g.height() - 60)};
    Vec2d paddleScl{150, 50};
    Vec2d cubePos{100, 100};
    Vec2d cubeScl{50, 50};
    Vec2d enmPaddleScl{150, 50};
    Vec2d enmPaddlePos{cubePos.x + (enmPaddleScl.x / 2), 60};
    Vec2d velocity{5, 5};
    float enmVelocity{0.1};
    double c = 1;
    int lives{3};
    Image skull(g, "skullG.gif");
    Sound badBone(g, "sounds/bad.mp3");
    while (g.draw()) {
        cubePos.x += (velocity.x);
        cubePos.y += (velocity.y);
        enmPaddlePos.x += enmVelocity * (cubePos.x - enmPaddlePos.x) * 0.1;
        if(cubePos.x <= 0){
            velocity.x *= -1;
        }
        if(cubePos.x >= g.width() - cubeScl.x){
            velocity.x *= -1;
        }
        if(cubePos.y <= 0){
            g.println("Winner!");
        }
        if(((cubePos.y >= paddlePos.y - cubeScl.y) && (((cubePos.x + cubeScl.x) >= paddlePos.x) && (cubePos.x <= (paddlePos.x + paddleScl.x))) && velocity.y > 0) || (cubePos.y <= enmPaddlePos.y + enmPaddleScl.y) && (((cubePos.x + cubeScl.x) >= enmPaddlePos.x) && (cubePos.x <= (enmPaddlePos.x + enmPaddleScl.x))) && velocity.y < 0){
            velocity.y *= -1;
            c += 0;
        }
        if(cubePos.y >= g.height()){
            lives--;
            //g.play(badBone);
            velocity.y = 10;
            cubePos = {100, 100};
        }
        if (g.isKeyPressed(Key::Left)){
            paddlePos.x -= 4 * (g.width() / 200);
        }
        if (g.isKeyPressed(Key::Right)){
            paddlePos.x += 4 * (g.width() / 200);
        }
        
        g.rect(enmPaddlePos, enmPaddleScl.x, enmPaddleScl.y, WHITE, RED);
        g.rect(paddlePos, paddleScl.x, paddleScl.y, RED, WHITE);
        g.rect(cubePos, cubeScl.x, cubeScl.y, WHITE, WHITE);
        g.image(cubePos, cubeScl.x, cubeScl.y, skull);
        g.println("{}", lives);
        g.println("{}", cubePos.x);
        if(lives <= 0){
            break;
            velocity.x += 1;
            velocity.y += 1;
        }
    }
}
