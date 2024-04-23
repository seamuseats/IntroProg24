#include "bullet.h"

using namespace std;

double radius = 20;

bool Bullet::checkCollision(Vec2d obj){
    if(sqrt(pow(pos.x - obj.x, 2) + pow(pos.y - obj.y, 2)) < radius){
        return true;
    }
    return false;
}

void Bullet::draw(Graphics& g){
    g.ellipse(pos, 20, 20, GREY, GREY);
    Vec2d velocity2 = Vec2d{0, 4}.rotated(rot + (M_PI / 2)) + velocity;
    pos += velocity2;
}
