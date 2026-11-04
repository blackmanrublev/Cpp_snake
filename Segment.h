#pragma once

#include "Tween.h"

class Segment
{
    double x;
    double y;
    double size;
    double draw_x;
    double draw_y;
    double draw_size;
    Tween x_tween;
    Tween y_tween;

public:
    Segment() = default;
    Segment(double _x, double _y, double _size, double _draw_size, float _duration);

    double getX(void) const;

    void setX(double _x);

    double getY(void) const;

    void setY(double _y);

    double getSize(void) const;

    double getDrawX() const;

    void setDrawX(double _draw_x);
    
    double getDrawY() const;

    void setDrawY(double _draw_y);
        
    double getDrawSize() const;
        
    void setDrawSize(double _draw_size);

    Tween& getXTween();
    
    Tween& getYTween();
};