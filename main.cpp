#include <math.h>
#include <vector>
#include <iostream>
#include "raylib.h"

const int win_width = 400;
const int win_height = 400;
float dt = 0;
float FPS = 0;

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

    ClearBackground(BLACK);

    EndDrawing();
}