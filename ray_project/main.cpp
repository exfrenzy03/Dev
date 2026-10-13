#include <iostream>
#include "raylib.h"
#include <vector>

#pragma comment(lib, "raylib.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "ucrt.lib")
#pragma comment(lib, "vcruntime.lib")
#pragma comment(lib, "msvcrt.lib")

#include "sandOperator.h"
using namespace std;

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Dusen Kum Simulasyonu");
    SetTargetFPS(60); 
    vector<sand> sands;
    int point = 0;
    
    while (!WindowShouldClose())
    {
        point += getPoint(sands);
        updateSands(sands);
        BeginDrawing();
        ClearBackground(GRAY);
        DrawText(TextFormat("%d", point), 20, 20, 30, PURPLE);
        
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            int mx = GetMouseX();
            int my = GetMouseY();
            int col = mx / pixel;
            int row = my / pixel;
            
            if (col >= 0 && col < COL && row >= 0 && row < ROW)
            {
                if (grid[col][row] == 0)
                {
                    sands.push_back(sand(mx, my));
                    grid[col][row] = 1;
                }
            }
        }
        
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            int mx = GetMouseX();
            int my = GetMouseY();
            int col = mx / pixel;
            int row = my / pixel;
            
            if (col >= 0 && col < COL && row >= 0 && row < ROW && grid[col][row] == 0)
            {
                sands.push_back(sand(mx, my));
                grid[col][row] = 1;
            }
        }
        
        drawSands(sands);
        EndDrawing();
    }
    return 0;
}