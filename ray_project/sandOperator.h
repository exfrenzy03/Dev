#include <iostream>
#include "raylib.h"
#include <vector>
using namespace std;

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;
const int pixel = 25;
const int ROW = SCREEN_HEIGHT / pixel;
const int COL = SCREEN_WIDTH / pixel;
bool grid[COL][ROW] = {0};
vector<Color> colorList = {RED, YELLOW, GREEN, BLUE};
// srand(time(NULL));

struct blockInfo
{
    Vector2 position[4];
    Color blockColor;
};
vector<blockInfo> blocks = {
    {{{0, 0}, {1, 0}, {2, 0}, {3, 0}}, colorList[rand() % 4]},
    {{{0, 0}, {0, -1}, {1, 0}, {2, 0}}, colorList[rand() % 4]},
    {{{0, 0}, {1, 0}, {2, 0}, {2, -1}}, colorList[rand() % 4]},
    {{{0, 0}, {1, 0}, {0, -1}, {1, -1}}, colorList[rand() % 4]},
    {{{0, 0}, {1, 0}, {1, -1}, {2, -1}}, colorList[rand() % 4]},
    {{{0, 0}, {1, 0}, {2, 0}, {1, -1}}, colorList[rand() % 4]},
    {{{0, 0}, {1, 0}, {0, -1}, {-1, -1}}, colorList[rand() % 4]}};

class sand
{
public:
    int x_coordinate;
    int y_coordinate;
    Color color;

    sand(int x, int y, Color c)
    {
        x_coordinate = (x / pixel) * pixel;
        y_coordinate = (y / pixel) * pixel;
        color = c;
    }

    void draw() const
    {
        DrawRectangle(x_coordinate, y_coordinate, pixel, pixel, color);
    }

    void update()
    {
        int row = y_coordinate / pixel;
        int col = x_coordinate / pixel;
        if (row + 1 < ROW)
        {
            if (grid[col][row + 1] == 0)
            {
                grid[col][row] = 0;
                y_coordinate += pixel;
                grid[col][row + 1] = 1;
            }
            else
            {
                if (grid[col + 1][row + 1] == 0)
                {
                    grid[col][row] = 0;
                    x_coordinate += pixel;
                    y_coordinate += pixel;
                    grid[col + 1][row + 1] = 1;
                }
                else
                {
                    if (grid[col - 1][row + 1] == 0)
                    {
                        grid[col][row] = 0;
                        x_coordinate -= pixel;
                        y_coordinate += pixel;
                        grid[col - 1][row + 1] = 1;
                    }
                }
            }
        }
    }
};

void clearRow(int targetRow)
{
    for (int i = 0; i < COL; i++)
    {
        grid[i][targetRow] = 0;
    }
}

void drawSands(const vector<sand> &sands)
{
    for (int i = 0; i < sands.size(); i++)
    {
        sands[i].draw();
    }
}

void updateSands(vector<sand> &sands)
{
    for (int i = 0; i < sands.size(); i++)
    {
        sands[i].update();
    }
}

int getPoint(vector<sand> &sands)
{
    for (int i = ROW - 1; i >= 0; i--)
    {
        bool rowFullAndSettled = true;

        for (int j = 0; j < COL; j++)
        {
            if (grid[j][i] == 0 || (i + 1 < ROW && grid[j][i + 1] == 0))
            {
                rowFullAndSettled = false;
                break;
            }
        }

        if (rowFullAndSettled)
        {
            for (int k = sands.size() - 1; k >= 0; k--)
            {
                if (sands[k].y_coordinate / pixel == i)
                {
                    sands.erase(sands.begin() + k);
                }
            }
            clearRow(i);
            return 10;
        }
    }
    return 0;
}