#include "Snake.h"
#include "raylib.h"


void Snake::control()
{
    std::pair<int, int> last_direction = direction_queue.empty() ? direction : direction_queue.back();

    if (IsKeyPressed(KEY_UP) && (last_direction.second != size))
    {
        direction_queue.push_back({0, -size});
    }
    if (IsKeyPressed(KEY_DOWN) && (last_direction.second != -size))
    {
        direction_queue.push_back({0, size});
    }
    if (IsKeyPressed(KEY_LEFT) && (last_direction.first != size))
    {
        direction_queue.push_back({-size, 0});
    }
    if (IsKeyPressed(KEY_RIGHT) && (last_direction.first != -size))
    {
        direction_queue.push_back({size, 0});
    }
}

Snake::Snake(float _speed, int _size) : size(_size), speed(_speed)
{
    direction = {20, 0};
    body.emplace_back(20, 20, size, size - 5, speed);
    // body.emplace_back(0, 20, cell_size, cell_size - 5, speed);
    last = body.back();
}

void Snake::update(float dt)
{
    timer += dt;
    if (timer >= speed)
    {
        overlap = false;
        eaten = false;
        timer = 0;
        last = body.back();

        if (direction_queue.size() > 0)
        {
            direction = direction_queue[0];
            direction_queue.pop_front();
        }

        for (int i = static_cast<int>(body.size()) - 1; i >= 0; i--)
        {
            Segment &segment = body[i];

            if (i == 0)
            {
                segment.setX(segment.getX() + direction.first);
                segment.setY(segment.getY() + direction.second);
            }
            else
            {
                segment.setX(body[i - 1].getX());
                segment.setY(body[i - 1].getY());
            }

            if (segment.getX() == last.getX() && segment.getY() == last.getY())
            {
                overlap = true;
            }
        }
    }
    control();
    tween(dt);
}

void Snake::eat()
{
    body.emplace_back(last.getX(), last.getY(), last.getSize(), last.getDrawSize(), speed);
    eaten = true;
}

void Snake::tween(float dt)
{
    for (auto& segment : body){              
        if (segment.getDrawX() != segment.getX() && segment.getXTween().isTweening() == false)
        {
            segment.getXTween().startTween(segment.getDrawX(), segment.getX());
        }              
        if (segment.getDrawY() != segment.getY() && segment.getYTween().isTweening() == false)
        {
            segment.getYTween().startTween(segment.getDrawY(), segment.getY());
        }            
        if (segment.getXTween().isTweening() == true)
        {
            segment.getXTween().update(dt);
        }
        if (segment.getYTween().isTweening() == true)
        {
            segment.getYTween().update(dt);
        }
        segment.setDrawX(segment.getXTween().getCurrentValue()); 
        segment.setDrawY(segment.getYTween().getCurrentValue()); 
    }
}

void Snake::draw()
{
    for (int i = body.size() - 1; i >= 0; i--)
    {
        Segment segment = body[i];
        if (i == 0){
            DrawCircle(segment.getDrawX() + segment.getSize() / 2, segment.getDrawY() + segment.getSize() / 2, segment.getDrawSize() / 2, GREEN);

        }
        else
        {
            if (i % 2 == 0){
                DrawRectangle(segment.getDrawX() + (segment.getSize() / 2 - segment.getDrawSize() / 2), segment.getDrawY() + (segment.getSize() / 2 - segment.getDrawSize() / 2), segment.getDrawSize(), segment.getDrawSize(), GREEN);
            }else{
                DrawRectangle(segment.getDrawX() + (segment.getSize() / 2 - segment.getDrawSize() / 2), segment.getDrawY() + (segment.getSize() / 2 - segment.getDrawSize() / 2), segment.getDrawSize(), segment.getDrawSize(), DARKGREEN);}
        }
    }
}

bool Snake::hasEaten()
{
    return eaten;
}

bool Snake::isOverlapping()
{
    return overlap;
}

std::vector<Segment>& Snake::getBody()
{
    return body;
}

Segment Snake::getLast()
{
    return last;
}