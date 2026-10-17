#include <iostream>
#include "raylib.h"
#include <vector>
#include <queue>
using namespace std;

const int SCREEN_WIDTH = 1500;
const int SCREEN_HEIGHT = 900;
const int pixel = 10;
const int ROW = SCREEN_HEIGHT / pixel;
const int COL = SCREEN_WIDTH / pixel;
int grid[COL][ROW] = {0};
vector<Color> colorList = {RED, YELLOW, GREEN, BLUE};
// srand(time(NULL));

struct blockInfo
{
    Vector2 position[4];
    Color blockColor;
};
vector<blockInfo> blocks = {
    {{{0, 0}, {1, 0}, {2, 0}, {3, 0}}, colorList[1]},
    {{{0, 1}, {0, 0}, {1, 1}, {2, 1}}, colorList[1]},
    {{{0, 1}, {1, 1}, {2, 1}, {2, 0}}, colorList[1]},
    {{{0, 1}, {1, 1}, {0, 0}, {1, 0}}, colorList[1]},
    {{{0, 1}, {1, 1}, {1, 0}, {2, 0}}, colorList[1]},
    {{{0, 1}, {1, 1}, {2, 1}, {1, 0}}, colorList[1]},
    {{{1, 1}, {2, 1}, {1, 0}, {0, 0}}, colorList[1]},
};

class sand
{
public:
    int x_coordinate;
    int y_coordinate;
    Color color;
    int colorID;

    sand(int x, int y, Color c, int id)
    {
        x_coordinate = (x / pixel) * pixel;
        y_coordinate = (y / pixel) * pixel;
        color = c;
        colorID = id;
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
                grid[col][row + 1] = colorID;
            }
            else
            {
                if (grid[col + 1][row + 1] == 0 && col + 1 < COL)
                {
                    grid[col][row] = 0;
                    x_coordinate += pixel;
                    y_coordinate += pixel;
                    grid[col + 1][row + 1] = colorID;
                }
                else
                {
                    if (grid[col - 1][row + 1] == 0 && col - 1 >= 0)
                    {
                        grid[col][row] = 0;
                        x_coordinate -= pixel;
                        y_coordinate += pixel;
                        grid[col - 1][row + 1] = colorID;
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

void activeBlockFall(vector<sand> &activeBlock, vector<sand> &sands)
{
    if (activeBlock.empty())
    {
        return;
    }
    bool canFall = 1;
    for (int i = 0; i < activeBlock.size(); i++)
    {
        int col = activeBlock[i].x_coordinate / pixel;
        int row = activeBlock[i].y_coordinate / pixel;
        if (row + 1 < ROW && grid[col][row + 1] == 0)
        {
            canFall = 1;
        }
        else
        {
            canFall = 0;
            break;
        }
    }
    if (canFall)
    {
        for (int i = 0; i < activeBlock.size(); i++)
        {
            activeBlock[i].y_coordinate += pixel;
        }
    }
    else
    {
        for (int i = 0; i < activeBlock.size(); i++)
        {
            sands.push_back(activeBlock[i]);
            grid[activeBlock[i].x_coordinate / pixel][activeBlock[i].y_coordinate / pixel] = activeBlock[i].colorID;
        }
        activeBlock.clear();
    }
}

void createBlock(vector<sand> &activeBlock)
{
    if (activeBlock.size() == 0)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            int mx = GetMouseX();
            int my = GetMouseY();
            int col = mx / pixel;
            int row = my / pixel;
            int randomShape = GetRandomValue(0, 6);
            int randomColor = GetRandomValue(0, 3);
            int thickness = 5;

            if (col >= 0 && col < COL && row >= 0 && row < ROW)
            {
                for (int i = 0; i < 4; i++)
                {
                    int baseX = mx + (blocks[randomShape].position[i].x * pixel * thickness);
                    int baseY = my + (blocks[randomShape].position[i].y * pixel * thickness);
                    for (int dx = 0; dx < thickness; dx++)
                    {
                        for (int dy = 0; dy < thickness; dy++)
                        {
                            int calculatedX = baseX + (dx * pixel);
                            int calculatedY = baseY + (dy * pixel);
                            int calculatedCol = calculatedX / pixel;
                            int calculatedRow = calculatedY / pixel;
                            if (calculatedCol >= 0 && calculatedCol < COL && calculatedRow >= 0 && calculatedRow < ROW)
                            {
                                if (grid[calculatedCol][calculatedRow] == 0)
                                {
                                    activeBlock.push_back(sand(calculatedX, calculatedY, colorList[randomColor], randomColor + 1));
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void updateActiveBlock(vector<sand> &activeBlock)
{
    if (IsKeyDown(KEY_LEFT) == 1)
    {
        bool canMove = 0;
        for (int i = 0; i < activeBlock.size(); i++)
        {
            int col = activeBlock[i].x_coordinate / pixel;
            int row = activeBlock[i].y_coordinate / pixel;
            if (col - 1 >= 0 && grid[col - 1][row] == 0)
            {
                canMove = 1;
            }
            else
            {
                canMove = 0;
                break;
            }
        }
        for (int i = 0; i < activeBlock.size(); i++)
        {
            if (canMove)
            {
                activeBlock[i].x_coordinate -= pixel;
            }
        }
    }

    if (IsKeyDown(KEY_RIGHT) == 1)
    {
        bool canMove = 0;
        for (int i = 0; i < activeBlock.size(); i++)
        {
            int col = activeBlock[i].x_coordinate / pixel;
            int row = activeBlock[i].y_coordinate / pixel;
            if (col + 1 < COL && grid[col + 1][row] == 0)
            {
                canMove = 1;
            }
            else
            {
                canMove = 0;
                break;
            }
        }
        for (int i = 0; i < activeBlock.size(); i++)
        {
            if (canMove)
            {
                activeBlock[i].x_coordinate += pixel;
            }
        }
    }
}
int getPoint(vector<sand> &sands)
{
    bool visited[COL][ROW] = {0};
    for (int row = 0; row < ROW; row++)
    {
        if (grid[0][row] != 0 && visited[0][row] == 0)
        {
            int targetColor = grid[0][row];
            bool bridgeConnected = false;
            queue<pair<int, int>> toVisit;
            vector<pair<int, int>> sandToRemove;
            toVisit.push(make_pair(0, row));
            visited[0][row] = 1;
            while (!toVisit.empty())
            {
                int x = toVisit.front().first;
                int y = toVisit.front().second;
                toVisit.pop();
                sandToRemove.push_back(make_pair(x, y));
                if (x == COL - 1)
                {
                    bridgeConnected = true;
                }
                int directionX[] = {1, -1, 0, 0};
                int directionY[] = {0, 0, 1, -1};
                for (int i = 0; i < 4; i++)
                {
                    int nx = x + directionX[i];
                    int ny = y + directionY[i];
                    if (nx >= 0 && nx < COL && ny >= 0 && ny < ROW)
                    {
                        if (grid[nx][ny] == targetColor && visited[nx][ny] == 0)
                        {
                            visited[nx][ny] = 1;
                            toVisit.push(make_pair(nx, ny));
                        }
                    }
                }
            }
            if (bridgeConnected)
            {
                bool removeMap[COL][ROW] = {0};
                for (int i = 0; i < sandToRemove.size(); i++)
                {
                    removeMap[sandToRemove[i].first][sandToRemove[i].second] = 1;
                    grid[sandToRemove[i].first][sandToRemove[i].second] = 0;
                }
                for (int k = sands.size() - 1; k >= 0; k--)
                {
                    int col = sands[k].x_coordinate / pixel;
                    int row = sands[k].y_coordinate / pixel;
                    if (removeMap[col][row] == 1)
                    {
                        sands.erase(sands.begin() + k);
                    }
                }
                return 100;
            }
        }
    }
    return 0;
}