#include <cmath>
#include <vector>
#include <iostream>
#include <string>
#include <deque>
#include <random>
#include "raylib.h"

std::mt19937 rng{std::random_device{}()};

const int win_width = 400;
const int win_height = 400;
const int cell_size = 20;
float dt = 0;
float FPS = 0;

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
    Tween(double _initial_value, double _final_value, float _duration) : initial_value(_initial_value), final_value(_final_value), current_value(_initial_value), duration(_duration) {}

    void startTween(float a, float b)
    {
        initial_value = a;
        final_value = b;
        difference = final_value - initial_value;
        start = true;
        timer = 0;
    }

    void update(float dt)
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

    bool isTweening()
    {
        return start;
    }

    void cancelTween()
    {
        start = false;
    }

    double getCurrentValue()
    {
        return current_value;
    }
};

class Cell
{
    int x;
    int y;
    int world_x;
    int world_y;
    std::string space;

public:
    Cell(int _x, int _y, int _world_x, int _world_y) : x(_x), y(_y), world_x(_world_x), world_y(_world_y) {}

    int getX(void) const
    {
        return x;
    }

    int getY(void) const
    {
        return y;
    }

    int getWorldX(void) const
    {
        return world_x;
    }

    int getWorldY(void) const
    {
        return world_y;
    }

    std::string getSpace(void) const
    {
        return space;
    }

    void setSpace(std::string _space)
    {
        space = _space;
    }
};

class Grid
{
    std::vector<Cell> spaces;
    int size;
    int width;
    int height;
    int width_in_cells;
    int height_in_cells;
    std::uniform_int_distribution<int> r_x;
    std::uniform_int_distribution<int> r_y;

public:
    Grid(int _size, int _width, int _height) : size(_size), width(_width), height(_height)
    {
        width_in_cells = measureInCells(width);
        height_in_cells = measureInCells(height);
        r_x = std::uniform_int_distribution<int>(0, (width / size) - 1);
        r_y = std::uniform_int_distribution<int>(0, (height / size) - 1);

        int grid_x_count = width / size;
        int grid_y_count = height / size;

        for (int grid_y = 0; grid_y < grid_y_count; grid_y++)
        {
            for (int grid_x = 0; grid_x < grid_x_count; grid_x++)
            {
                Cell a(grid_x, grid_y, grid_x * size, grid_y * size);
                spaces.push_back(a);
            }
        }
    }

    void draw()
    {
        for (const Cell &cell : spaces)
        {
            DrawRectangleLines(cell.getWorldX(), cell.getWorldY(), cell_size, cell_size, WHITE);

            DrawText(cell.getSpace().c_str(), cell.getWorldX(), cell.getWorldY(), 18, WHITE);
        }
    }

    int measureInCells(int a)
    {
        return a / size;
    }

    int convertToIndex(const std::pair<int, int> coord)
    {
        int i;
        if (measureInCells(coord.first) > width_in_cells - 1 || measureInCells(coord.second) > height_in_cells - 1 || measureInCells(coord.first) < 0 || measureInCells(coord.second) < 0)
        {
            return -1;
        }
        else
        {
            i = (coord.first / size) + (coord.second / size) * (width / size);
        }

        if ((i < 0) || i >= spaces.size())
        {
            return -1;
        }
        else
        {
            return i;
        }
    }

    std::pair<int, int> getRandomCell()
    {
        for (int i = 0; i <= 15 + static_cast<int>(std::log10(static_cast<int>(spaces.size()))); i++)
        {
            int x = r_x(rng) * size;
            int y = r_y(rng) * size;
            if (spaces[convertToIndex({x, y})].getSpace() == "")
            {
                return {x, y};
            }
        }

        for (int i = 0; i < static_cast<int>(spaces.size()); i++)
        {
            if (spaces[i].getSpace() == "")
            {
                return {spaces[i].getWorldX(), spaces[i].getWorldY()};
            }
        }
    }

    int getSize(void) const
    {
        return size;
    }

    int getWidth(void) const
    {
        return width;
    }

    int getHeight(void) const
    {
        return height;
    }

    auto &getSpaces(void)
    {
        return spaces;
    }
};

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
    Segment(double _x, double _y, double _size, double _draw_size, float _duration) : x(_x), y(_y), size(_size), draw_x(_x), draw_y(_y), draw_size(_draw_size), x_tween(_x, _x, _duration), y_tween(_y, _y, _duration){}

    double getX(void) const
    {
        return x;
    }

    void setX(int _x)
    {
        x = _x;
    }

    double getY(void) const
    {
        return y;
    }

    void setY(int _y)
    {
        y = _y;
    }

    double getSize(void) const
    {
        return size;
    }

    double getDrawX() const
    {
        return draw_x;
    }

    void setDrawX(double _draw_x)
    {
        draw_x = _draw_x;
    }
    
    double getDrawY() const
    {
        return draw_y;
    }

    void setDrawY(double _draw_y)
    {
        draw_y = _draw_y;
    }
        
    double getDrawSize() const
    {
        return draw_size;
    }
        
    void setDrawSize(double _draw_size)
    {
        draw_size = _draw_size;
    }

    Tween& getXTween()
    {
        return x_tween;
    }
    
    Tween& getYTween()
    {
        return y_tween;
    }
};

class Snake
{
    std::vector<Segment> body;
    Segment last;
    std::pair<int, int> direction;
    std::deque<std::pair<int, int>> direction_queue;
    float speed;
    float timer;
    int step;
    bool eaten;
    bool overlap;

    void control()
    {
        std::pair<int, int> last_direction = direction_queue.empty() ? direction : direction_queue.back();

        if (IsKeyPressed(KEY_UP) && (last_direction.second != step))
        {
            direction_queue.push_back({0, -step});
        }
        if (IsKeyPressed(KEY_DOWN) && (last_direction.second != -step))
        {
            direction_queue.push_back({0, step});
        }
        if (IsKeyPressed(KEY_LEFT) && (last_direction.first != step))
        {
            direction_queue.push_back({-step, 0});
        }
        if (IsKeyPressed(KEY_RIGHT) && (last_direction.first != -step))
        {
            direction_queue.push_back({step, 0});
        }
    }

public:
    Snake(int step) : step(step)
    {
        direction = {20, 0};
        speed = 0.25;
        body.emplace_back(20, 20, cell_size, cell_size - 5, speed);
        body.emplace_back(0, 20, cell_size, cell_size - 5, speed);
        last = body.back();
    }

    bool update(float dt)
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
            control();
            tween(dt);
            return true;
        }
        control();
        tween(dt);
        return false;
    }

    void eat()
    {
        body.emplace_back(last.getX(), last.getY(), last.getSize(), last.getDrawSize(), speed);
        eaten = true;
    }

    void tween(float dt)
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

    void draw(void)
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

    bool hasEaten()
    {
        return eaten;
    }

    bool isOverlapping()
    {
        return overlap;
    }

    auto& getBody(void)
    {
        return body;
    }

    Segment getLast(void)
    {
        return body.back();
    }
};

class Apple
{
    double x;
    double y;
    double size;
    double draw_x;
    double draw_y;
    double draw_size;

public:
    Apple() : x(0), y(0), size(0) {}
    Apple(int _x, int _y, int _size, int _draw_size) : x(_x), y(_y), size(_size), draw_size(_draw_size) {}

    void draw(void)
    {
        DrawRectangle(x + (size / 2 - draw_size / 2), y + (size / 2 - draw_size / 2), draw_size, draw_size, RED);
    }

    double getX(void) const
    {
        return x;
    }

    void setX(int _x)
    {
        x = _x;
    }

    double getY(void) const
    {
        return y;
    }

    void setY(int _y)
    {
        y = _y;
    }

    int getSize(void) const
    {
        return size;
    }
};

Snake snake(cell_size);

Grid grid(20, win_width, win_height);

Apple apple(100, 20, cell_size, cell_size - 10);

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
        Segment &segment = snake.getBody()[i];
        int index = grid.convertToIndex({segment.getX(), segment.getY()});
        if (index != -1)
        {
            grid.getSpaces()[grid.convertToIndex({segment.getX(), segment.getY()})].setSpace("snake");
        }
    }

    grid.getSpaces()[grid.convertToIndex({apple.getX(), apple.getY()})].setSpace("apple");
}

void UpdateGame(float dt)
{
    snake.update(dt);
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
                grid.getSpaces()[grid.convertToIndex({apple.getX(), apple.getY()})].setSpace("");
                apple.setX(x);
                apple.setY(y);
                grid.getSpaces()[grid.convertToIndex({apple.getX(), apple.getY()})].setSpace("apple");
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
        grid.getSpaces()[head_grid_index].setSpace("snake");
    }

    if (last_grid_index != -1 && snake.hasEaten() == false && snake.isOverlapping() == false)
    {
        grid.getSpaces()[last_grid_index].setSpace("");
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