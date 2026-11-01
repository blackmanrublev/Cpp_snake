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

class Cell{
    int x;
    int y;
    int world_x;
    int world_y;
    std::string space;

    public:
        Cell(int x, int y, int world_x, int world_y) : x(x), y(y), world_x(world_x), world_y(world_y) {}

        int getX(void) const{
            return x;
        }
        
        int getY(void) const{
            return y;
        }
        
        int getWorldX(void) const{
            return world_x;
        }
        
        int getWorldY(void) const{
            return world_y;
        }
        
        std::string getSpace(void) const{
            return space;
        }   

        void setSpace(std::string _space){
            space = _space;
        }
        
};

class Grid{
    std::vector<Cell> spaces;
    int size;
    int width;
    int height;
    int width_in_cells;
    int height_in_cells;
    std::uniform_int_distribution<int> r_x;
    std::uniform_int_distribution<int> r_y;

    public:
        Grid(int _size, int _width, int _height) : size(_size), width(_width), height(_height) {
            width_in_cells = measureInCells(width);
            height_in_cells = measureInCells(height);
            r_x = std::uniform_int_distribution<int>(0, (width / size) - 1);
            r_y = std::uniform_int_distribution<int>(0, (height / size) - 1);

            int grid_x_count = width / size;
            int grid_y_count = height / size;

            for (int grid_y = 0; grid_y < grid_y_count; grid_y++){
                for (int grid_x = 0; grid_x < grid_x_count; grid_x++){
                    Cell a(grid_x, grid_y, grid_x * size, grid_y * size);
                    spaces.push_back(a);
                }
            }
            
        }

        void draw(){
            for (const Cell& cell : spaces){
                DrawRectangleLines(cell.getWorldX(), cell.getWorldY(), cell_size, cell_size, WHITE);

                DrawText(cell.getSpace().c_str(), cell.getWorldX(), cell.getWorldY(), 18, WHITE);
            }
        }

        int measureInCells(int a){
            return a / size;
        }

        int convertToIndex(const std::pair<int, int> coord){
            int i;
            if (measureInCells(coord.first) > width_in_cells - 1 || measureInCells(coord.second) > height_in_cells - 1 || measureInCells(coord.first) < 0 || measureInCells(coord.second) < 0){
                return -1;
            }else{
                i = (coord.first / size) + (coord.second / size) * (width / size);
            }

            if ((i < 0) || i >= spaces.size()){
                return -1;
            }else{
                return i;
            }
        }

        std::pair<int, int> getRandomCell(){
            for (int i = 0; i <= 15 + static_cast<int>(std::log10(static_cast<int>(spaces.size()))); i++){
                int x = r_x(rng) * size;
                int y = r_y(rng) * size;
                if (spaces[convertToIndex({x, y})].getSpace() == ""){
                    return {x, y};
                }
            }

            for(int i = 0; i < static_cast<int>(spaces.size()); i++){
                if (spaces[i].getSpace() == ""){
                    return {spaces[i].getX(), spaces[i].getY()};
                }
            }
        }
        
        int getSize(void) const{
            return size;
        }
        
        int getWidth(void) const{
            return width;
        }
        
        int getHeight(void) const{
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
                
        int getX(void) const{
            return x;
        }
                                 
        void setX(int _x){
            x = _x;
        }

        int getY(void) const{
            return y;
        }
                
        void setY(int _y){
            y = _y;
        }
                
        int getSize(void) const{
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
    bool eaten;
    bool overlap;
    
    void control(){
        std::pair<int, int> last_direction = direction_queue.empty() ? direction : direction_queue.back(); 
        
        if (IsKeyPressed(KEY_UP) && (last_direction.second != step)){
            direction_queue.push_back({0, -step});
        }
        if (IsKeyPressed(KEY_DOWN) && (last_direction.second != -step)){
            direction_queue.push_back({0, step});
        }
        if (IsKeyPressed(KEY_LEFT) && (last_direction.first != step)){
            direction_queue.push_back({-step, 0});
        }
        if (IsKeyPressed(KEY_RIGHT) && (last_direction.first != -step)){
            direction_queue.push_back({step, 0});
        }
    }


    public:
        Snake(int step) : step(step) {
            Segment s(20, 20, cell_size);
            Segment d(0, 20, cell_size);
            body.push_back(s);
            body.push_back(d);
            direction = {20, 0};
            speed = 0.25;
        }

        bool update(float dt){
            timer += dt;
            if (timer > speed){
                overlap = false;
                eaten = false;
                timer -= speed;
                last = body[(static_cast<int>(body.size())) - 1];

                if (direction_queue.size() > 0){
                    direction = direction_queue[0];
                    direction_queue.pop_front();
                }

                for (int i = static_cast<int>(body.size()) - 1; i >= 0; i--){
                    Segment& segment = body[i];

                    if (i == 0){
                        segment.setX(segment.getX() + direction.first);
                        segment.setY(segment.getY() + direction.second);
                    }else{
                        segment.setX(body[i -1].getX());
                        segment.setY(body[i -1].getY());
                    }
                    
                    if (segment.getX() == last.getX() && segment.getY() == last.getY()){
                        overlap = true;
                    }
                }
                control();
                return true;
            }
            control();
            return false;
        }
        
        void eat(){
            body.push_back(last);
            eaten = true;
        }

        void draw(void){
            for (const Segment& segment : body){
                DrawRectangle(segment.getX(), segment.getY(), cell_size, cell_size, GREEN);
            }
        }

        bool hasEaten(){
            return eaten;
        }

        bool isOverlapping(){
            return overlap;
        }

        auto& getBody(void){
            return body;
        }

        float getTImer(void){
            return timer;
        }

        Segment getLast(void){
            return last;
        }
};


class Apple{
    int x;
    int y;
    int size;

    public:
        Apple() : x(0), y(0), size(0) {}
        Apple(int x, int y, int size) : x(x), y(y), size(size) {} 
        
        void draw(void) {
            DrawRectangle(x, y, cell_size, cell_size, RED);
        }
                
        int getX(void) const{
            return x;
        }
                                 
        void setX(int _x){
            x = _x;
        }

        int getY(void) const{
            return y;
        }
                
        void setY(int _y){
            y = _y;
        }
                
        int getSize(void) const{
            return size;
        }
};

Snake snake(cell_size);

Grid grid(20, win_width, win_height);

Apple apple(100, 20, cell_size);

void InitGame(void);
void UpdateGame(float dt);
void DrawGame(void);

int main(void) {
    InitGame();

    while(!WindowShouldClose()){
        dt = GetFrameTime();
        FPS = roundf(1.0f / dt);

        UpdateGame(dt);

        DrawGame();
    }

    return 0;
}

void InitGame(void){
    InitWindow(win_width, win_height, "snake");
    SetTargetFPS(60);

    for (int i = 0; i < snake.getBody().size(); i++){
        Segment& segment = snake.getBody()[i];
        int index = grid.convertToIndex({segment.getX(), segment.getY()});
        if (index != -1){
            grid.getSpaces()[grid.convertToIndex({segment.getX(), segment.getY()})].setSpace("snake");
        }
    }
    
    grid.getSpaces()[grid.convertToIndex({apple.getX(), apple.getY()})].setSpace("apple");

}

void UpdateGame(float dt){
    if (snake.update(dt)){
        bool eaten = false;
        int head_grid_index = grid.convertToIndex({snake.getBody()[0].getX(), snake.getBody()[0].getY()});
        int last_grid_index = grid.convertToIndex({snake.getLast().getX(), snake.getLast().getY()});
        
        if (snake.getBody()[0].getX() == apple.getX() && snake.getBody()[0].getY() == apple.getY()){
            snake.eat();
            if (snake.hasEaten()){
                if (static_cast<int>(snake.getBody().size()) < static_cast<int>(grid.getSpaces().size())){
                    auto [x, y] = grid.getRandomCell();
                    grid.getSpaces()[grid.convertToIndex({apple.getX(), apple.getY()})].setSpace("");
                    apple.setX(x);
                    apple.setY(y);
                    grid.getSpaces()[grid.convertToIndex({apple.getX(), apple.getY()})].setSpace("apple");
                }else{
                    apple.setX(-1000);
                    apple.setY(-1000);
                }
            }
        }

        if (head_grid_index != -1){
            grid.getSpaces()[head_grid_index].setSpace("snake");
        }

        if (last_grid_index != -1 && snake.hasEaten() == false && snake.isOverlapping() == false){
            grid.getSpaces()[last_grid_index].setSpace("");
        }
    }

}

void DrawGame(void){
    BeginDrawing();
    
    ClearBackground(BLACK);

    apple.draw();

    snake.draw();

    grid.draw();

    EndDrawing();
}