#include <iostream>
#include "raylib.h"
using namespace std;
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

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Dusen Kum Simulasyonu");
    SetTargetFPS(20);
    vector<sand> sands;
    int point = 0;
    while (!WindowShouldClose())
    {

        point += getPoint(sands);
        updateSands(sands);
        BeginDrawing();
        ClearBackground(GRAY);
        DrawText(TextFormat("%d", point), 20, 20, 30, PURPLE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            sands.push_back(sand(GetMouseX(), GetMouseY()));
        }
        drawSands(sands);
        EndDrawing();
    }
    return 0;
}