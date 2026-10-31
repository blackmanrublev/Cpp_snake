#include <math.h>
#include <vector>
#include <iostream>
#include <string>
#include <vector>
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
                
        int getY(void){
            return y;
        }
                
        int getSize(void){
            return size;
        }
};

class Snake{
    std::vector<Segment> body;
    Segment last;
    float update;
    bool eat;

    public:
        Snake(void) {
            Segment s(100, 100, cell_size);
            body.push_back(s);
        }

        void draw(void) {
            for (Segment segment : body){
                DrawRectangle(segment.getX(), segment.getY(), cell_size, cell_size, GREEN);
            }
        }
};

Snake snake;

Grid grid(20, win_width, win_height);

void InitGame(void);
void UpdateGame(void);
void DrawGame(void);

int main(void) {
    InitGame();

    while(!WindowShouldClose()){
        if (FPS > 0){
            FPS = roundf(1 / dt);
        }
        dt = GetFrameTime();

        UpdateGame();

        DrawGame();
    }

    return 0;
}

void InitGame(void){
    InitWindow(win_width, win_height, "snake");
    SetTargetFPS(1000);

}

void UpdateGame(void){
    
}

void DrawGame(void){
    BeginDrawing();

    snake.draw();

    grid.draw();

    ClearBackground(BLACK);

    EndDrawing();
}