
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include <iostream>
#include <math.h>
#include <map>
#include <algorithm>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;
#pragma comment(lib, "user32.lib")

int main()
{
    ma_engine engine;
    ma_result result = ma_engine_init(NULL, &engine);

    if (result != MA_SUCCESS)
    {
        cout << "Miniaudio motoru baslatilamadi" << endl;
        return -1;
    }

    map<char, string> keySoundMap{
        {'1', "sesler/kadin_surucu.mp3"},
        {'2', "sesler/gay.mp3"},
        {'3', "sesler/iett.mp3"},
        {'4', "sesler/memet_abi.mp3"},
        {'Q', "sesler/deagle.mp3"},
        {'R', "sesler/deagle.mp3"},
        {'T', "sesler/deagle.mp3"},
        {'Y', "sesler/deagle.mp3"},
        {'U', "sesler/deagle.mp3"},
        {'I', "sesler/deagle.mp3"},
        {'O', "sesler/deagle.mp3"},
        {'P', "sesler/deagle.mp3"},
        {'Ğ', "sesler/deagle.mp3"},
        {'Ü', "sesler/deagle.mp3"},
        {'A', "sesler/deagle.mp3"},
        {'S', "sesler/deagle.mp3"},
        {'D', "sesler/deagle.mp3"},
        {'F', "sesler/deagle.mp3"},
        {'G', "sesler/deagle.mp3"},
        {'H', "sesler/deagle.mp3"},
        {'J', "sesler/deagle.mp3"},
        {'K', "sesler/deagle.mp3"},
        {'L', "sesler/deagle.mp3"},
        {'Ş', "sesler/deagle.mp3"},
        {'İ', "sesler/deagle.mp3"},
        {'Z', "sesler/deagle.mp3"},
        {'X', "sesler/deagle.mp3"},
        {'C', "sesler/deagle.mp3"},
        {'V', "sesler/deagle.mp3"},
        {'B', "sesler/deagle.mp3"},
        {'N', "sesler/deagle.mp3"},
        {'M', "sesler/deagle.mp3"},
        {'Ö', "sesler/deagle.mp3"},
        {VK_SPACE, "sesler/reload.mp3"}
    };

    map<char, bool> keyState;

    cout << "Miniaudio baslatildi" << endl;
    cout << "1, 2, 3, 4, 5, 6, 7, 8, 9 ve 0 tuslarini kullanabilirsin" << endl;

    while (true)
    {
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        {
            break;
        }

        for (auto const &pair : keySoundMap)
        {
            char key = pair.first;
            string soundBoard = pair.second;
            bool isPressed = (GetAsyncKeyState(key) & 0x8000) != 0; // bu hesap (GetAsyncKeyState(key) & 0x8000 kodu bize 1 döndürüyor)

            if (isPressed && !keyState[key])
            {
                ma_engine_play_sound(&engine, soundBoard.c_str(), NULL);
                cout << "Ses tetiklendi: " << soundBoard << endl;
                keyState[key] = true;
            }
            else if (!isPressed && keyState[key])
            {
                keyState[key] = false;
            }
        }
        Sleep(10);
    }
    ma_engine_uninit(&engine);
    cout << "Program kapatildi" << endl;
    return 0;
}