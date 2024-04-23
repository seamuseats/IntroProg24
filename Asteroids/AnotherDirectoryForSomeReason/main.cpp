#include "graphics.h"
#include "rand.h"
#include "math.h"
#include "vec2d.h"
#include "ship.h"
#include "asteroid.h"
#include "bullet.h"

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

void collectPls(Array<Bullet> set, int i, Graphics& g){
    if(set[i].pos.x >= (g.width())){
        set.removeAtIndex(i);
    }
    if(set[i].pos.y >= (g.height())){
        set.removeAtIndex(i);
    }
    if(set[i].pos.x <= 0){
        set.removeAtIndex(i);
    }
    if(set[i].pos.y <= 0){
        set.removeAtIndex(i);
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
    int coolDown{0};
    Array<Bullet> sceneProjectiles;
    while(john.size() < 10){
        john.append(Asteroid({randomInt(0, g.width()), randomInt(0, g.height())}, {randomDouble(-1, 1), randomInt(-1, 1)}, {0, 0}, 25));
    }
    while (g.draw()) {
        // drawButton(g, {g.width() / 2, g.height() / 2}, "Plungors", 255);
        
        num ++;
        Vec2d centre{g.width() / 2, g.height() / 2};
        //P1.rot = 1 / sin((centre.y - P1.pos.y));
        g.rect({0, 0}, (1 / (coolDown / 30)) * g.width(), 10, RED, GREEN);
        if (g.isKeyPressed(Key::Space) && coolDown < 0){
            sceneProjectiles.append(Bullet(P1.pos, P1.velocity, P1.rot, 300));
            coolDown = 30;
            //for the funy
            #ifdef linux
            system("cat ./trollface.txt");
            #endif 
            #ifdef APPLE
            system("cat ./trollface.txt");
            #endif
            #ifdef _WIN32
            system("type trollface.txt");
            #endif
        }

        while(num % 500 == 0 && john.size() < 10){
            john.append(Asteroid({randomInt(0, g.width()), randomInt(0, g.height())}, {randomDouble(-1, 1), randomInt(-1, 1)}, {0, 0}, 25));
        }
        
        for (int i = 0; i < john.size(); i++){
            wrapper(g, john[i].pos);
            john[i].draw(g);
        }
        //while(sceneProjectiles.size() > 0){
        for (int i = 0; i < (sceneProjectiles.size()); i++){
            sceneProjectiles[i].life--;
            sceneProjectiles[i].draw(g);
            for(int a = 0; a < john.size(); a++){
                if(sceneProjectiles[i].checkCollision(john[a].pos)){
                    john.removeAtIndex(a);
                }
            }
            //collectPls(sceneProjectiles, i, g);
            
            
            wrapper(g, sceneProjectiles[i].pos);
            if(sceneProjectiles[i].life < 0){
                sceneProjectiles.removeAtIndex(i);
            }
        }
        //}

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
        coolDown--;
        // if(P1.velocity.y >= 3){
        //     P1.velocity.y = 5;
        // }
        P1.pos += P1.velocity;
        wrapper(g, P1.pos);
        g.println("{}", P1.rot);
        P1.draw(g);
    }
}
