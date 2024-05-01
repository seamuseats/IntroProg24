#ifndef DRAWINGCANVAS_H
#define DRAWINGCANVAS_H

#include "vec2d.h"

class DrawingColor
{
public:
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a{255};
public:
    constexpr DrawingColor(int c) : r((c >> 16)&0xFF), g((c >> 8)&0xFF), b(c&0xFF), a(0xFF) {}
    constexpr DrawingColor()  : r(0), g(0), b(0), a(255) {}
    constexpr DrawingColor(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a = 255)  : r(_r), g(_g), b(_b), a(_a) {}
    unsigned int toUIntRGBA() const { return a & (b << 8) & (g << 16) & (r << 24); }
    int toIntRGB() const { return b & (g << 8) & (r << 16); }
};

constexpr DrawingColor COLOR_TRANSPARENT{0,0,0,0};
constexpr DrawingColor COLOR_WHITE{255,255,255};
constexpr DrawingColor COLOR_GREY{128,128,128};
constexpr DrawingColor COLOR_BLACK{0,0,0};
constexpr DrawingColor COLOR_RED{255,0,0};
constexpr DrawingColor COLOR_GREEN{0,255,0};
constexpr DrawingColor COLOR_BLUE{0,0,255};
constexpr DrawingColor COLOR_YELLOW{255,255,0};
constexpr DrawingColor COLOR_PURPLE{255,0,255};
constexpr DrawingColor COLOR_CYAN{0,255,255};

class DrawingCanvas
{
public:
    virtual ~DrawingCanvas() {}
    virtual double width() = 0;
    virtual double height() = 0;
    virtual void line(Vec2d p1, Vec2d p2, DrawingColor color = COLOR_WHITE) = 0;
    virtual void rect(Vec2d lowerLeftCorner, double width, double height, DrawingColor stroke = COLOR_WHITE, DrawingColor fill = COLOR_TRANSPARENT) = 0;
    virtual void circle(Vec2d center, double diameter, DrawingColor stroke = COLOR_WHITE, DrawingColor fill = COLOR_TRANSPARENT) = 0;
    virtual void text(Vec2d lowerLeftCorner, double height, std::string str, DrawingColor color) = 0;
    virtual void polygon(std::vector<Vec2d> pts, DrawingColor stroke = COLOR_WHITE, DrawingColor fill = COLOR_TRANSPARENT) = 0;
    virtual void pie(Vec2d corner, double w, double h, double a, double alen, DrawingColor c = COLOR_WHITE, DrawingColor f = COLOR_TRANSPARENT) = 0;
    virtual void polyline(std::vector<Vec2d> pts, DrawingColor stroke = COLOR_WHITE) = 0;

};

#endif // DRAWINGCANVAS_H
