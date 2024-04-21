#include "ship.h"

using namespace mssm;

void Ship::draw(mssm::Graphics& g) {
  Array<Vec2d> pointes;

  Vec2d centre{g.width() / 2, g.height() / 2};

  pointes.append(Vec2d({1, 1}));
  pointes.append(Vec2d({0.4, 1.6}));
  pointes.append(Vec2d({-0.4, 1.6}));
  pointes.append(Vec2d({-1, 1}));
  pointes.append(Vec2d({-1, -1}));
  pointes.append(Vec2d({1, -1}));

  for (int i = 0; i < pointes.size(); i++) {
    pointes[i].rotate(rot + (M_PI / 2));
    pointes[i] *= size;
    pointes[i] += pos;
  }

  g.polygon(pointes, mssm::GREEN, GREEN);
}
