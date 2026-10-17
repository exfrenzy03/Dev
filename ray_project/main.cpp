#include <iostream>
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <vector>
#include <time.h>
#include <queue>
#include "sandOperator.h"
#include <algorithm>

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
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Arcade Sand Tetris");
    SetTargetFPS(50);
    vector<sand> sands;
    vector<sand> activeBlock;
    vector<int> oldScores;
    int point = 0;
    float fallTimer = 0.0f;
    float fallSpeed = 0.04f;
    bool isMainMenu = true;
    bool gameOver = false;

    initBlocks();

    // RayGUI Retro Makyajı (Sadece butonlara etki eder)
    GuiSetStyle(DEFAULT, TEXT_SIZE, 25);                                     // Yazı boyutu
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt({30, 30, 40, 255}));   // Koyu arkaplan
    GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, ColorToInt({60, 60, 80, 255}));  // Üzerine gelinceki renk
    GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, ColorToInt(BLACK));              // Tıklama rengi
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(WHITE));               // Yazı rengi
    GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, ColorToInt({0, 255, 255, 255})); // Üzerine gelince neon mavi yazı
    GuiSetStyle(BUTTON, BORDER_WIDTH, 4);                                    // Çerçeve kalınlığı
    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, ColorToInt(BLACK));             // Çerçeve rengi

    // Retro Arka Plan Renkleri
    Color bgDark = {15, 15, 20, 255};     // Oyun alanı (Çok koyu lacivert)
    Color uiDark = {25, 25, 35, 255};     // Sol panel
    Color panelColor = {40, 40, 50, 255}; // Kutular

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_F11))
        {
            ToggleFullscreen();
        }
        // Main Menu Ekranı
        if (isMainMenu)
        {
            BeginDrawing();
            ClearBackground(bgDark);

            // Arcade stili başlık
            DrawText("NEON SAND", SCREEN_WIDTH / 2 - 300, SCREEN_HEIGHT / 2 - 200, 100, {255, 0, 128, 255}); // Neon Pembe
            DrawText("TETRIS", SCREEN_WIDTH / 2 - 130, SCREEN_HEIGHT / 2 - 90, 80, {0, 255, 255, 255});      // Cyber Mavi

            DrawText("Ayni renkleri duvardan duvara birlestir, kopruyu patlat!", SCREEN_WIDTH / 2 - 280, SCREEN_HEIGHT / 2 + 30, 20, LIGHTGRAY);

            // Başla Butonu
            if (GuiButton({(float)SCREEN_WIDTH / 2 - 125, (float)SCREEN_HEIGHT / 2 + 100, 250, 70}, "OYUNA BASLA"))
            {
                isMainMenu = false;
                initBlocks();
            }

            EndDrawing();
            continue; // Menüdeyken aşağıdaki oyun kodlarını okumadan döngüyü başa sar
        }

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
        ClearBackground(bgDark);                              // Oyun alanı rengi
        DrawRectangle(0, 0, UI_WIDTH, SCREEN_HEIGHT, uiDark); // Sol arayüz bölmesi

        // Puan kutusu
        DrawRectangle(10, 10, UI_WIDTH - 20, 100, panelColor);
        DrawRectangleLinesEx({10, 10, (float)UI_WIDTH - 20, 100}, 5.0f, BLACK);
        DrawText(TextFormat("PUAN: %d", point), 30, 40, 40, WHITE);

        // Sıradaki Blok Kutusu
        DrawRectangle(10, 120, UI_WIDTH - 20, 300, panelColor);
        DrawRectangleLinesEx({10, 120, (float)UI_WIDTH - 20, 300}, 5.0f, BLACK);
        DrawText("SIRADAKI BLOK", 80, 150, 30, WHITE);
        showNextBlock(currentBlock);

        // Skor Tablosu Kutusu
        DrawRectangle(10, 430, UI_WIDTH - 20, SCREEN_HEIGHT - 440, panelColor);
        DrawRectangleLinesEx({10, 430, (float)UI_WIDTH - 20, (float)SCREEN_HEIGHT - 440}, 5.0f, BLACK);
        DrawText("SKOR TABLOSU", 85, 460, 30, WHITE);

        int textY = 520;
        int siralama = 1;

        for (int i = 0; i < oldScores.size(); i++)
        {
            // "Oyun" yerine "Skor" kelimesi daha şık duracaktır
            DrawText(TextFormat("%d. Skor:  %d Puan", siralama, oldScores[i]), 50, textY, 25, BLACK);
            textY += 35;
            siralama++;
        }

        // Ölüm çizgisi
        DrawLineEx({(float)UI_WIDTH, (float)DEATH_LINE_ROW * pixel}, {(float)SCREEN_WIDTH, (float)DEATH_LINE_ROW * pixel}, 5.0f, RED);

        // Kum çizdirme
        drawSands(activeBlock);
        drawSands(sands);

        // Gameover ekranı
        if (gameOver)
        {
            DrawRectangle(UI_WIDTH, 0, SCREEN_WIDTH - UI_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 0.9f));
            DrawRectangle(UI_WIDTH, SCREEN_HEIGHT / 2 - 150, SCREEN_WIDTH - UI_WIDTH, 300, Fade(BLACK, 0.95f));

            // Bandın alt ve üst sınırlarına kırmızı çizgi
            DrawLineEx({(float)UI_WIDTH, (float)(SCREEN_HEIGHT / 2 - 150)}, {(float)SCREEN_WIDTH, (float)(SCREEN_HEIGHT / 2 - 150)}, 5.0f, MAROON);
            DrawLineEx({(float)UI_WIDTH, (float)(SCREEN_HEIGHT / 2 + 150)}, {(float)SCREEN_WIDTH, (float)(SCREEN_HEIGHT / 2 + 150)}, 5.0f, MAROON);

            DrawText("OYUN BITTI!", UI_WIDTH + 330, SCREEN_HEIGHT / 2 - 100, 80, RED);
            DrawText("Yeniden baslamak icin 'R' tusuna bas", UI_WIDTH + 260, SCREEN_HEIGHT / 2 - 10, 30, LIGHTGRAY);

            bool restartRequested = false;

            // Butonu tam ortaya aldık
            if (GuiButton({(float)UI_WIDTH + 450, (float)SCREEN_HEIGHT / 2 + 50, 200, 60}, "TEKRAR OYNA"))
            {
                restartRequested = true;
            }
            if (IsKeyPressed(KEY_R))
            {
                restartRequested = true;
            }

            // Yeniden Başlatma İşlemleri ve Skoru Kaydetme
            if (restartRequested)
            {
                oldScores.push_back(point);
                sort(oldScores.begin(), oldScores.end(), greater<int>());
                if (oldScores.size() > 10)
                {
                    oldScores.pop_back();
                }

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