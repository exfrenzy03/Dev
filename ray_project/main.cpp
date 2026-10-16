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
    SetTargetFPS(120);
    vector<sand> sands;
    vector<sand> activeBlock;
    int point = 0;
    float fallTimer = 0.0f;
    float fallSpeed = 0.10f;
    while (!WindowShouldClose())
    {
        point += getPoint(sands);
        fallTimer += GetFrameTime();
        if (fallTimer >= fallSpeed)
        {
            activeBlockFall(activeBlock);
            updateSands(sands);
            fallTimer = 0.0f;
        }
        BeginDrawing();
        ClearBackground(GRAY);
        DrawText(TextFormat("%d", point), 20, 20, 30, PURPLE);
        createBlock(activeBlock);
        updateActiveBlock(activeBlock);
        drawSands(activeBlock);
        drawSands(sands);
        EndDrawing();
    }
    return 0;
}