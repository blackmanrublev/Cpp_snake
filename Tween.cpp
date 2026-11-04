#include "Tween.h"
#include <cmath>

Tween::Tween(double _initial_value, double _final_value, float _duration) : initial_value(_initial_value), final_value(_final_value), current_value(_initial_value), duration(_duration) {}

void Tween::startTween(float a, float b)
{
    initial_value = a;
    final_value = b;
    difference = final_value - initial_value;
    start = true;
    timer = 0;
}

void Tween::update(float dt)
{
    timer += dt;

    if (start == true){
        if (timer < duration)
        {
            // current_value = initial_value + (difference * (timer / duration));
            current_value = initial_value + (difference * (pow((timer / duration) - 1, 3) + 1));
        }
        else
        {
            start = false;
            timer = 0;
            current_value = final_value;
        }
    }
}

bool Tween::isTweening()
{
    return start;
}

void Tween::cancelTween()
{
    start = false;
}

double Tween::getCurrentValue()
{
    return current_value;
}