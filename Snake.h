#pragma once

#include <vector>
#include <deque>
#include "Segment.h"
#include "raylib.h"

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
    bool updated;
    bool overlap;

public:
    Snake(float _speed, int _size);
    
    void control(int key);

    void update(float dt);

    void eat();

    void tween(float dt);

    void draw();

    bool hasEaten();

    bool hasUpdated();

    bool isOverlapping();

    std::vector<Segment>& getBody();

    Segment& getLast();
};