#include <iostream>
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
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
    float fallSpeed = 0.04f;
    bool gameOver = false;

    initBlocks();

    while (!WindowShouldClose())
    {
        if (!gameOver)
        {
            point += getPoint(sands);
            fallTimer += GetFrameTime();
            // Hızlı düşürme mekanizması
            if (IsKeyDown(KEY_DOWN))
            {
                fallTimer += GetFrameTime() * 6.0f; // Süreyi 6 kat hızlandırıyoruz
            }
            if (fallTimer >= fallSpeed)
            {
                activeBlockFall(activeBlock, sands);
                updateSands(sands);
                fallTimer = 0.0f;
                for (int c = 0; c < COL; c++)
                {
                    if (grid[c][DEATH_LINE_ROW] != 0)
                    {
                        gameOver = true;
                        break;
                    }
                }
            }
            createBlock(activeBlock);
            updateActiveBlock(activeBlock);
        }
        BeginDrawing();

        ClearBackground(DARKGRAY);                               // Oyun alanı rengi
        DrawRectangle(0, 0, UI_WIDTH, SCREEN_HEIGHT, LIGHTGRAY); // Sol arayüz bölmesi

        // Puan kutusu
        DrawRectangle(10, 10, UI_WIDTH - 20, 100, GRAY);
        DrawRectangleLinesEx({10, 10, (float)UI_WIDTH - 20, 100}, 5.0f, BLACK);
        DrawText(TextFormat("PUAN: %d", point), 30, 40, 40, BLACK);

        // Sıradaki Blok Kutusu
        DrawRectangle(10, 120, UI_WIDTH - 20, 300, GRAY);
        DrawRectangleLinesEx({10, 120, (float)UI_WIDTH - 20, 300}, 5.0f, BLACK);
        DrawText("SIRADAKI BLOK", 80, 150, 30, BLACK);
        showNextBlock(currentBlock);

        // Skor Tablosu Kutusu
        DrawRectangle(10, 430, UI_WIDTH - 20, SCREEN_HEIGHT - 440, GRAY);
        DrawRectangleLinesEx({10, 430, (float)UI_WIDTH - 20, (float)SCREEN_HEIGHT - 440}, 5.0f, BLACK);
        DrawText("SKOR TABLOSU", 85, 460, 30, BLACK);

        // Ölüm çizgisi
        DrawLineEx({(float)UI_WIDTH, (float)DEATH_LINE_ROW * pixel}, {(float)SCREEN_WIDTH, (float)DEATH_LINE_ROW * pixel}, 5.0f, LIGHTGRAY);

        // Kum çizdirme
        drawSands(activeBlock);
        drawSands(sands);

        // Gameover ekranı
        if (gameOver)
        {
            DrawRectangle(UI_WIDTH, 0, SCREEN_WIDTH - UI_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 0.7f));
            DrawText("OYUN BITTI!", UI_WIDTH + 275, SCREEN_HEIGHT / 2 - 80, 80, RED);
            DrawText("Yeniden baslamak icin 'R' tusuna bas", UI_WIDTH + 250, SCREEN_HEIGHT / 2 + 50, 30, LIGHTGRAY);

            // R Tuşu ile Yeniden Başlatma İşlemi
            if (IsKeyPressed(KEY_R))
            {
                gameOver = false;
                sands.clear();
                activeBlock.clear();
                for (int c = 0; c < COL; c++)
                    for (int r = 0; r < ROW; r++)
                        grid[c][r] = 0;
                point = 0;
                currentBlock.shapeIndex = -1;
                initBlocks();
            }
        }
        EndDrawing();
    }
    return 0;
}