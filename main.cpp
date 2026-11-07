#include <cmath>
#include <vector>
#include <iostream>
#include <string>
#include <deque>
#include <random>
#include "raylib.h"
#include "Grid.h"
#include "Tween.h"
#include "Snake.h"
#include "Apple.h"

const int win_width = 400;
const int win_height = 400;
const int cell_size = 20;
float dt = 0;
float FPS = 0;
float _speed = 0.13;

Snake snake(_speed, cell_size);

Grid grid(20, win_width, win_height);

Apple apple(100, 20, cell_size - 10, cell_size, _speed);

void InitGame(void);
void UpdateGame(float dt);
void DrawGame(void);

int main(void)
{
    InitGame();

    while (!WindowShouldClose())
    {
        dt = GetFrameTime();
        FPS = roundf(1.0f / dt);

        UpdateGame(dt);

        DrawGame();
    }

    return 0;
}

void InitGame(void)
{
    InitWindow(win_width, win_height, "snake");
    SetTargetFPS(60);

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
}

void UpdateGame(float dt)
{
    snake.update(dt);
    apple.update(dt);
    int head_grid_index = grid.convertToIndex({snake.getBody()[0].getX(), snake.getBody()[0].getY()});
    int last_grid_index = grid.convertToIndex({snake.getLast().getX(), snake.getLast().getY()});

    if (snake.getBody()[0].getX() == apple.getX() && snake.getBody()[0].getY() == apple.getY())
    {
        snake.eat();
        if (snake.hasEaten())
        {
            if (static_cast<int>(snake.getBody().size()) < static_cast<int>(grid.getSpaces().size()))
            {
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

    if (head_grid_index != -1)
    {
        grid.getSpaces()[head_grid_index].space = Space::Snake;
    }

    if (last_grid_index != -1 && snake.hasEaten() == false && snake.isOverlapping() == false)
    {
        grid.getSpaces()[last_grid_index].space = Space::Empty;
    }
}

void DrawGame(void)
{
    BeginDrawing();

    ClearBackground(BLACK);

    apple.draw();

    snake.draw();

    // grid.draw();

    EndDrawing();
}