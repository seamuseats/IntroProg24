#ifndef GRAPHICSCANVAS_H
#define GRAPHICSCANVAS_H

#include "botbattle/drawingcanvas.h"

namespace mssm {
class Graphics;
}

class GraphicsCanvas : public DrawingCanvas
{
    mssm::Graphics& g;
public:
    GraphicsCanvas(mssm::Graphics& g);
    double width() override;
    double height() override;
    void line(Vec2d p1, Vec2d p2, DrawingColor color= COLOR_WHITE)  override;
    void rect(Vec2d lowerLeftCorner, double width, double height, DrawingColor stroke = COLOR_WHITE, DrawingColor fill = COLOR_TRANSPARENT)  override;
    void circle(Vec2d center, double diameter, DrawingColor stroke = COLOR_WHITE, DrawingColor fill = COLOR_TRANSPARENT)  override;
    void text(Vec2d lowerLeftCorner, double height, std::string str, DrawingColor color)  override;
    void polygon(std::vector<Vec2d> pts, DrawingColor stroke = COLOR_WHITE, DrawingColor fill = COLOR_TRANSPARENT) override;
    void pie(Vec2d corner, double w, double h, double a, double alen, DrawingColor c = COLOR_WHITE, DrawingColor f = COLOR_TRANSPARENT) override;
    void polyline(std::vector<Vec2d> pts, DrawingColor stroke = COLOR_WHITE) override;
};

#endif // GRAPHICSCANVAS_H
