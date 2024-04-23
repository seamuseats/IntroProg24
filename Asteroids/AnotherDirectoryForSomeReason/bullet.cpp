#include "bullet.h"

using namespace std;

double radius = 20;

bool Bullet::checkCollision(Vec2d obj){
    if(sqrt((pow(pos.x, 2) - pow(obj.x, 2)) + (pow(pos.y, 2) - pow(obj.y, 2))) < radius){
        return true;
    }
    return false;
}

void Bullet::draw(Graphics& g){
    g.ellipse(pos, 20, 20, GREY, GREY);
}