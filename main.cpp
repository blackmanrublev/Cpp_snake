// #include <cmath>
// #include <vector>
// #include <iostream>
// #include <random>
// #include <string>
// #include <vector>
#include <deque>
#include "raylib.h"
#include "Grid.h"
#include "Tween.h"
#include "Snake.h"
#include "Apple.h"
#include "ParticleEmitter.h"
// #include "Profiler.h"

// #define PLATFORM_WEB

#if defined(PLATFORM_WEB)
    #include <emscripten.h>
#endif

struct Counter{
    int value;
    int set_x;
    int set_y;
};

const int win_width = 400;
const int win_height = 400;
const int cell_size = 20;
float dt = 0;
float _speed = 0.13;
// bool print_report = false;
std::deque<Counter> counters{};
std::deque<int> sett_x{};
std::deque<int> sett_y{};
int set_x = 0;
int set_y = 0;

Snake snake(_speed, cell_size);

Grid grid(20, win_width, win_height);

Apple apple(100, 20, cell_size - 10, cell_size, _speed);

ParticleEmitter emitter(0, 0, cell_size, _speed, 20, _speed * 2);

// Profiler profile;

void InitGame();
void UpdateGame(float dt);
void DrawGame();
void UpdateDraw();
void CounterDraw();

int main()
{
    InitGame();

    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop(UpdateDraw, 0, 1);
    #else

        while (!WindowShouldClose())
        {
            UpdateDraw();
        }
    #endif

    return 0;
}

void InitGame()
{
    // profile.start("Init");
    InitWindow(win_width, win_height, "snake");
    
    SetTargetFPS(60);

    grid.initTexture();

    for (int i = 0; i < snake.getBody().size(); i++)
    {
        Segment& segment = snake.getBody()[i];
        int index = grid.convertToIndex({segment.getX(), segment.getY()});
        if (index != -1)
        {
            grid.getSpaces()[grid.convertToIndex({segment.getX(), segment.getY()})].space = Space::Snake;
        }
    }

    grid.getSpaces()[grid.convertToIndex({apple.getX(), apple.getY()})].space = Space::Apple;
    // profile.stop();
    // profile.report();
}

void UpdateGame(float dt)
{
    snake.control(GetKeyPressed());
    snake.update(dt);
    apple.update(dt);
    emitter.update(dt);
    int head_grid_index = grid.convertToIndex({snake.getBody()[0].getX(), snake.getBody()[0].getY()});
    int last_grid_index = grid.convertToIndex({snake.getLast().getX(), snake.getLast().getY()});

    if (snake.getBody()[0].getX() == apple.getX() && snake.getBody()[0].getY() == apple.getY())
    {
        // print_report = true;
        snake.eat();
        if (snake.hasEaten())
        {
            if (static_cast<int>(snake.getBody().size()) < static_cast<int>(grid.getSpaces().size()))
            {
                emitter.setX(apple.getX());
                emitter.setY(apple.getY());
                emitter.emitParticles();
                auto [x, y] = grid.getRandomCell();
                grid.getSpaces()[grid.convertToIndex({apple.getX(), apple.getY()})].space = Space::Empty;
                apple.setX(x);
                apple.setY(y);
                apple.setDrawX(x);
                apple.setDrawY(y);
                apple.getXTween().startTween(apple.getDrawX(), apple.getX());
                apple.getYTween().startTween(apple.getDrawY(), apple.getY());
                apple.setDrawSize(0);
                grid.getSpaces()[grid.convertToIndex({apple.getX(), apple.getY()})].space = Space::Apple;
            }
            else
            {
                apple.setX(-1000);
                apple.setY(-1000);
            }
        }
    }  

    if (snake.hasUpdated() == true)
    {
        auto& body = snake.getBody();
        for (Counter& counter : counters)
        {
            if (counter.value >= 1 && counter.value < body.size())
            {
                if (counter.set_x != 0)
                {
                    body[counter.value].setDrawX(counter.set_x);
                    body[counter.value].getXTween().setInitialValue(counter.set_x);
                }
                else if (counter.set_y != 0)
                {
                    body[counter.value].setDrawY(counter.set_y);
                    body[counter.value].getYTween().setInitialValue(counter.set_y);
                }
                counter.value++;
            }
            else
            {
                counters.pop_back();
            }
        }
        if (body[0].getX() < 0)
        {
            set_x = win_width;
            body[0].setX(set_x - cell_size);
            body[0].setDrawX(set_x);
            body[0].getXTween().setFinalValue(body[0].getX());
            body[0].getXTween().setInitialValue(body[0].getDrawX());
            counters.push_front({1, set_x, 0});
        }
        else if (body[0].getX() > win_width - cell_size)
        {
            set_x = -cell_size;
            body[0].setX(set_x + cell_size);
            body[0].setDrawX(set_x);
            body[0].getXTween().setFinalValue(body[0].getX());
            body[0].getXTween().setInitialValue(body[0].getDrawX());
            counters.push_front({1, set_x, 0});
        }
        else if (body[0].getY() < 0)
        {
            set_y = win_height;
            body[0].setY(set_y - cell_size);
            body[0].setDrawY(set_y);
            body[0].getYTween().setFinalValue(body[0].getY());
            body[0].getYTween().setInitialValue(body[0].getDrawY());
            counters.push_front({1, 0, set_y});
        }
        else if (body[0].getY() > win_height - cell_size)
        {
            set_y = -cell_size;
            body[0].setY(set_y + cell_size);
            body[0].setDrawY(set_y);
            body[0].getYTween().setFinalValue(body[0].getY());
            body[0].getYTween().setInitialValue(body[0].getDrawY());
            counters.push_front({1, 0, set_y});
        }
    }
    

    if (head_grid_index != -1)
    {
        grid.getSpaces()[head_grid_index].space = Space::Snake;
    }

    if (last_grid_index != -1 && snake.hasEaten() == false && snake.isOverlapping() == false)
    {
        grid.getSpaces()[last_grid_index].space = Space::Empty;
    }
    // profile.stop();
}

void DrawGame()
{
    // profile.start("Draw");
    BeginDrawing();

    ClearBackground(BLACK);

    apple.draw();

    snake.draw();

    emitter.draw();

    CounterDraw();

    // DrawText(std::to_string(snake.getBody().size()).c_str(), 0, 0, 20, WHITE);

    // DrawText(std::to_string(dt).c_str(), 100, 0, 20, WHITE);
    
    // grid.draw();

    // profile.stop();
    EndDrawing();
}


void UpdateDraw()
{
    dt = GetFrameTime();
    UpdateGame(dt);
    DrawGame();
}

void CounterDraw()
{
    int shift_x = 0;
    int shift_y = 0;
    auto& body = snake.getBody();

    for (Counter counter : counters)
    {
        if (counter.set_x != 0)
        {
            if (counter.set_x > 0)
            {
                shift_x = -win_width;
            }
            else
            {
                shift_x = win_width;
            }
        }
        if (counter.set_y != 0)
        {
            if (counter.set_y > 0)
            {
                shift_y = -win_height;
            }
            else
            {
                shift_y = win_height;
            }
        }
        if (counter.value == 1)
        {
            DrawCircle(body[counter.value - 1].getDrawX() + body[counter.value - 1].getSize() / 2 + shift_x, body[counter.value - 1].getDrawY() + body[counter.value - 1].getSize() / 2 + shift_y, body[counter.value - 1].getDrawSize() / 2, GREEN);
        }
        else
        {
            if (counter.value > 0)
            {
                if (counter.value % 2 == 1)
                {
                    DrawRectangle(body[counter.value - 1].getDrawX() + (body[counter.value - 1].getSize() / 2 - body[counter.value - 1].getDrawSize() / 2) + shift_x, body[counter.value - 1].getDrawY() + (body[counter.value - 1].getSize() / 2 - body[counter.value - 1].getDrawSize() / 2) + shift_y, body[counter.value - 1].getDrawSize(), body[counter.value - 1].getDrawSize(), GREEN);
                }
                else
                {
                    DrawRectangle(body[counter.value - 1].getDrawX() + (body[counter.value - 1].getSize() / 2 - body[counter.value - 1].getDrawSize() / 2) + shift_x, body[counter.value - 1].getDrawY() + (body[counter.value - 1].getSize() / 2 - body[counter.value - 1].getDrawSize() / 2) + shift_y, body[counter.value - 1].getDrawSize(), body[counter.value - 1].getDrawSize(), DARKGREEN);
                }
            }
        }
    }
}