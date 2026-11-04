#include "Apple.h"
#include "raylib.h"


Apple::Apple() : x(0), y(0), size(0), cell_size(0), speed(0) {}
Apple::Apple(int _x, int _y, int _size, double _cell_size, float _speed) : x(_x), y(_y), draw_x(_x), draw_y(_y), size(_size), draw_size(_size), cell_size(_cell_size), speed(_speed), x_tween(_x, _x, _speed), y_tween(_y, _y, _speed), size_tween(_size, _size, _speed) {}

void Apple::update(float dt)
{              
    if (draw_x != x && x_tween.isTweening() == false)
    {
        x_tween.startTween(draw_x, x);
    }              
    if (draw_y != y && y_tween.isTweening() == false)
    {
        y_tween.startTween(draw_y, y);
    }              
    if (draw_size != size && size_tween.isTweening() == false)
    {
        size_tween.startTween(draw_size, size);
    }              
    if (x_tween.isTweening() == true)
    {
        x_tween.update(dt);
    }
    if (y_tween.isTweening() == true)
    {
        y_tween.update(dt);
    }
    if (size_tween.isTweening() == true)
    {
        size_tween.update(dt);
    }
    draw_x = x_tween.getCurrentValue(); 
    draw_y = y_tween.getCurrentValue(); 
    draw_size = size_tween.getCurrentValue(); 

}

void Apple::draw(void)
{
    DrawRectangle(draw_x + (cell_size / 2 - draw_size / 2), draw_y + (cell_size / 2 - draw_size / 2), draw_size, draw_size, RED);
}

double Apple::getX(void) const
{
    return x;
}

void Apple::setX(double _x)
{
    x = _x;
}

double Apple::getY(void) const
{
    return y;
}

void Apple::setY(double _y)
{
    y = _y;
}

double Apple::getSize(void) const
{
    return size;
}

double Apple::getDrawX() const
{
    return draw_x;
}

void Apple::setDrawX(double _draw_x)
{
    draw_x = _draw_x;
}

double Apple::getDrawY() const
{
    return draw_y;
}

void Apple::setDrawY(double _draw_y)
{
    draw_y = _draw_y;
}
    
double Apple::getDrawSize() const
{
    return draw_size;
}
    
void Apple::setDrawSize(double _draw_size)
{
    draw_size = _draw_size;
}

Tween& Apple::getXTween()
{
    return x_tween;
}

Tween& Apple::getYTween()
{
    return y_tween;
}

Tween& Apple::getSizeTween()
{
    return size_tween;
}
