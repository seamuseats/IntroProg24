#include "graphics.h"
#include "rand.h"
#include "math.h"
#include "vec2d.h"
#include "ship.h"
#include "asteroid.h"

using namespace std;
using namespace mssm;

void wrapper(Graphics& g, Vec2d& pos){
    Vec2d centre{g.width() / 2, g.height() / 2};
    if(pos.x >= (g.width())){
        pos.x -= (g.width());
    }
    if(pos.y >= (g.height())){
        pos.y -= (g.height());
    }
    if(pos.x <= 0){
        pos.x += g.width();
    }
    if(pos.y <= 0){
        pos.y += g.height();
    }
}



int main(int argc, char *argv[])
{
    Graphics g("Pluh", 1024, 768);
    Image skull(g, "skullG.gif");
    Sound badBone(g, "sounds/bad.mp3");
    Array<Asteroid> john;
    Ship P1;
    P1.pos = {0, 0};
    P1.accel = {0, 0};
    int num = 0;
    Vec2d vCopy = {P1.velocity};
    while (g.draw()) {
        // drawButton(g, {g.width() / 2, g.height() / 2}, "Plungors", 255);
        
        num ++;
        Vec2d centre{g.width() / 2, g.height() / 2};
        //P1.rot = 1 / sin((centre.y - P1.pos.y));
        if(num % 8 == 0){
            while(john.size() < 10){
                john.append(Asteroid({randomInt(0, g.width()), randomInt(0, g.height())}, {randomDouble(-1, 1), randomInt(-1, 1)}, {0, 0}, 10));
            }
        }
        for (int i = 0; i < john.size(); i++){
            wrapper(g, john[i].pos);
            john[i].draw(g);
        }
        if (g.isKeyPressed(Key::Left)){
            P1.rot -= 0.05;
        }
        else if(g.isKeyPressed(Key::Right)){
            P1.rot += 0.05;
        }
        else if(g.isKeyPressed(Key::Up)){
            P1.accel = Vec2d{0.1, 0}.rotated(P1.rot);
            P1.velocity -= P1.accel * 0.5;
        }
        else{
            P1.accel *= 0.999;
        }
        P1.velocity *= 0.999;
        // if(P1.velocity.y >= 3){
        //     P1.velocity.y = 5;
        // }
        P1.pos += P1.velocity;
        wrapper(g, P1.pos);
        g.println("{}", P1.rot);
        P1.draw(g);
    }
}
