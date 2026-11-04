#pragma once

class Tween
{
    double initial_value;
    double final_value;
    double current_value;
    float duration;
    float timer;
    float difference;
    bool start = false;

public:
    Tween() = default;
    Tween(double _initial_value, double _final_value, float _duration);

    void startTween(float a, float b);

    void update(float dt);

    bool isTweening();

    void cancelTween();

    double getCurrentValue();
};