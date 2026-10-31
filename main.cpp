#include <math.h>
#include <vector>
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include "raylib.h"

const int win_width = 400;
const int win_height = 400;
const int cell_size = 20;
float dt = 0;
float FPS = 0;

class Cell{
    int x;
    int y;
    int world_x;
    int world_y;
    std::string space;

    public:
        Cell(int x, int y, int world_x, int world_y) : x(x), y(y), world_x(world_x), world_y(world_y) {}

        int getX(void){
            return x;
        }
        
        int getY(void){
            return y;
        }
        
        int getWorldX(void){
            return world_x;
        }
        
        int getWorldY(void){
            return world_y;
        }
        
        std::string getSpace(void){
            return space;
        }
        
};

class Grid{
    std::vector<Cell> spaces;
    int size;
    int width;
    int height;

    public:
        Grid(int size, int width, int height) : size(size), width(width), height(height) {
            int grid_x_count = width / size;
            int grid_y_count = width / size;

            for (int grid_y = 0; grid_y < grid_y_count; grid_y++){
                for (int grid_x = 0; grid_x < grid_x_count; grid_x++){
                    Cell a(grid_x, grid_y, grid_x * size, grid_y * size);
                    spaces.push_back(a);
                }
            }
            
        }

        void draw(){
            for (Cell cell : spaces){
                DrawRectangleLines(cell.getWorldX(), cell.getWorldY(), cell_size, cell_size, WHITE);
            }
        }

        int convertToCoord(int a){
            return a / size;
        }
        
        int getSize(void){
            return size;
        }
        
        int getWidth(void){
            return width;
        }
        
        int getHeight(void){
            return height;
        }

        auto& getSpaces(void){
            return spaces;
        }
};

class Segment{
    int x;
    int y;
    int size;

    public:
        Segment() : x(0), y(0), size(0) {}
        Segment(int x, int y, int size) : x(x), y(y), size(size) {} 
                
        int getX(void){
            return x;
        }
                                 
        void setX(int _x){
            x = _x;
        }

        int getY(void){
            return y;
        }
                
        void setY(int _y){
            y = _y;
        }
                
        int getSize(void){
            return size;
        }
};
class Snake{
    std::vector<Segment> body;
    Segment last;
    std::pair<int, int> direction;
    std::deque<std::pair<int, int>> direction_queue;
    float speed;
    float timer;
    int step;
    bool eat;
    
    void control(){
        if (IsKeyPressed(KEY_UP)){
            direction_queue.push_back({0, -step});
        }
        if (IsKeyPressed(KEY_DOWN)){
            direction_queue.push_back({0, step});
        }
        if (IsKeyPressed(KEY_LEFT)){
            direction_queue.push_back({-step, 0});
        }
        if (IsKeyPressed(KEY_RIGHT)){
            direction_queue.push_back({step, 0});
        }
    }

    public:
        Snake(int step) : step(step) {
            Segment s(100, 100, cell_size);
            body.push_back(s);
            direction = {20, 0};
            speed = 0.5;
        }

        void update(float dt){
            timer += dt;
            if (timer > speed){
                timer = 0.0;

                if (direction_queue.size() > 0){
                    direction = direction_queue[0];
                    direction_queue.pop_front();
                }

                for (int i = 0; i < (int)body.size(); i++){
                    Segment& segment = body[i];

                    if (i == 0){
                        segment.setX(segment.getX() + direction.first);
                        segment.setY(segment.getY() + direction.second);
                        
                        std::cout << segment.getX();
                    }
                }
            }
            control();
        }

        void draw(void) {
            for (Segment segment : body){
                DrawRectangle(segment.getX(), segment.getY(), cell_size, cell_size, GREEN);
            }
        }
};

Snake snake(cell_size);

Grid grid(20, win_width, win_height);

void InitGame(void);
void UpdateGame(float dt);
void DrawGame(void);

int main(void) {
    InitGame();

    while(!WindowShouldClose()){
        if (FPS > 0){
            FPS = roundf(1 / dt);
        }
        dt = GetFrameTime();

        UpdateGame(dt);

        DrawGame();
    }

    return 0;
}

void InitGame(void){
    InitWindow(win_width, win_height, "snake");
    SetTargetFPS(1000);

}

void UpdateGame(float dt){
    snake.update(dt);
    
}

void DrawGame(void){
    BeginDrawing();

    snake.draw();

    grid.draw();

    ClearBackground(BLACK);

    EndDrawing();
}