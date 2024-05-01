#include "graphicscanvas.h"
#include "graphics.h"

using namespace mssm;

constexpr mssm::Color toColor(DrawingColor &dc) {
    return mssm::Color{dc.r, dc.g, dc.b, dc.a};
}

GraphicsCanvas::GraphicsCanvas(Graphics& g)
    : g{g}
{

}

double GraphicsCanvas::width()
{
    return g.width();
}

double GraphicsCanvas::height()
{
    return g.height();
}

void GraphicsCanvas::line(Vec2d p1, Vec2d p2, DrawingColor color)
{
    g.line(p1,p2,toColor(color));
}

void GraphicsCanvas::rect(Vec2d lowerLeftCorner, double width, double height, DrawingColor stroke, DrawingColor fill)
{
    g.rect(lowerLeftCorner, width, height, toColor(stroke), toColor(fill));
}

void GraphicsCanvas::circle(Vec2d center, double diameter, DrawingColor stroke, DrawingColor fill)
{
    g.ellipse(center, diameter, diameter, toColor(stroke), toColor(fill));
}

void GraphicsCanvas::text(Vec2d lowerLeftCorner, double height, std::string str, DrawingColor color)
{
    g.text(lowerLeftCorner, height, str, toColor(color));
}

void GraphicsCanvas::polygon(std::vector<Vec2d> pts, DrawingColor stroke, DrawingColor fill)
{
    g.polygon(pts, toColor(stroke), toColor(fill));
}

void GraphicsCanvas::pie(Vec2d corner, double w, double h, double a, double alen, DrawingColor c, DrawingColor f)
{
    g.pie(corner, w, h, a, alen, toColor(c), toColor(f));

}

void GraphicsCanvas::polyline(std::vector<Vec2d> pts, DrawingColor stroke)
{
    g.polyline(pts, toColor(stroke));

}
