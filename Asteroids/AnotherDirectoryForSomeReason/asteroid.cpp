#include "asteroid.h"

void wrap(Graphics& g, Vec2d& pos){
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

void Asteroid::draw(Graphics& g){
    wrap(g, pos);
    g.ellipse(pos, size, size, WHITE, WHITE);
    pos += velocity;
}