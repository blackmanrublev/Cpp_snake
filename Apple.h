#pragma once

#include "Tween.h"

class Apple
{
    double x;
    double y;
    double size;
    double cell_size;
    double draw_x;
    double draw_y;
    double draw_size;
    float speed;
    Tween x_tween;
    Tween y_tween;
    Tween size_tween;

public:
    Apple();
    Apple(int _x, int _y, int _size, double _cell_size, float _speed);

    void update(float dt);

    void draw();

    double getX() const;

    void setX(double _x);

    double getY() const;

    void setY(double _y);

    double getSize() const;

    double getDrawX() const;

    void setDrawX(double _draw_x);
    
    double getDrawY() const;

    void setDrawY(double _draw_y);
        
    double getDrawSize() const;
        
    void setDrawSize(double _draw_size);

    Tween& getXTween();
    
    Tween& getYTween();

    Tween& getSizeTween();
};
