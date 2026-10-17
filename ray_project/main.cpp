#include <iostream>
#include "raylib.h"
#include <vector>
#include <time.h>
#include <queue>
#include "sandOperator.h"

#pragma comment(lib, "raylib.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "ucrt.lib")
#pragma comment(lib, "vcruntime.lib")
#pragma comment(lib, "msvcrt.lib")

using namespace std;

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Dusen Kum Simulasyonu");
    SetTargetFPS(50);
    vector<sand> sands;
    vector<sand> activeBlock;
    int point = 0;
    float fallTimer = 0.0f;
    float fallSpeed = 0.02f;
    while (!WindowShouldClose())
    {
        point += getPoint(sands);
        fallTimer += GetFrameTime();
        if (fallTimer >= fallSpeed)
        {
            activeBlockFall(activeBlock,sands);
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