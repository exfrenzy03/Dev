#include <iostream>
#include "raylib.h"
#include <vector>
#include <time.h>

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
    SetTargetFPS(15);
    vector<sand> sands;
    int point = 0;
    float fallTimer = 0.0;
    float fallSpeed = 0.5;
    while (!WindowShouldClose())
    {
        point += getPoint(sands);
        updateSands(sands);
        if (fallTimer >= fallSpeed)
        {
            fallTimer = 0.0;
        }
        else
        {
            fallTimer += GetFrameTime();
        }
        BeginDrawing();
        ClearBackground(GRAY);
        DrawText(TextFormat("%d", point), 20, 20, 30, PURPLE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            int mx = GetMouseX();
            int my = GetMouseY();
            int col = mx / pixel;
            int row = my / pixel;
            int randomShape = GetRandomValue(0, 6);

            if (col >= 0 && col < COL && row >= 0 && row < ROW)
            {
                if (grid[col][row] == 0)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        int calculatedX = mx + blocks[randomShape].position[i].x * pixel;
                        int calculatedY = my + blocks[randomShape].position[i].y * pixel;
                        int calculatedCol = calculatedX / pixel;
                        int calculatedRow = calculatedY / pixel;
                        sands.push_back(sand(calculatedX, calculatedY, blocks[randomShape].blockColor));
                        grid[calculatedCol][calculatedRow] = 1;
                    }
                }
            }
        }

        drawSands(sands);
        EndDrawing();
    }
    return 0;
}