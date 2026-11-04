#pragma once

#include <vector>
#include <deque>
#include "Segment.h"

class Snake
{
    std::vector<Segment> body;
    Segment last;
    std::pair<int, int> direction;
    std::deque<std::pair<int, int>> direction_queue;
    float speed;
    float timer;
    int size;
    bool eaten;
    bool overlap;

    void control();

public:
    Snake(float _speed, int _size);

    void update(float dt);

    void eat();

    void tween(float dt);

    void draw(void);

    bool hasEaten();

    bool isOverlapping();

    std::vector<Segment>& getBody(void);

    Segment getLast(void);
};