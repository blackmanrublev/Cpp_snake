#include "Segment.h"

Segment::Segment(double _x, double _y, double _size, double _draw_size, float _duration) : x(_x), y(_y), size(_size), draw_x(_x), draw_y(_y), draw_size(_draw_size), x_tween(_x, _x, _duration), y_tween(_y, _y, _duration){}

double Segment::getX(void) const
{
    return x;
}

void Segment::setX(double _x)
{
    x = _x;
}

double Segment::getY(void) const
{
    return y;
}

void Segment::setY(double _y)
{
    y = _y;
}

double Segment::getSize(void) const
{
    return size;
}

double Segment::getDrawX() const
{
    return draw_x;
}

void Segment::setDrawX(double _draw_x)
{
    draw_x = _draw_x;
}

double Segment::getDrawY() const
{
    return draw_y;
}

void Segment::setDrawY(double _draw_y)
{
    draw_y = _draw_y;
}
    
double Segment::getDrawSize() const
{
    return draw_size;
}
    
void Segment::setDrawSize(double _draw_size)
{
    draw_size = _draw_size;
}

Tween& Segment::getXTween()
{
    return x_tween;
}

Tween& Segment::getYTween()
{
    return y_tween;
}