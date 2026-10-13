#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include <math.h>
#include <vector>
#include <algorithm>

int main()
{
    int deger1;
    int deger2;
    int ebob;
    int check;
    cout << "Ilk degeri gir" << endl;
    cin >> deger1;
    cout << "Ikinci degeri gir" << endl;
    cin >> deger2;
    if (deger1 <= deger2)
        check = deger1;
    else
        check = deger2;
    for (int i = 1; i <= check; i++)
    {
        if (deger1 % i == 0 && deger2 % i == 0)
        {
            ebob = i;
        }
    }
    int ekok = deger1 * deger2 / ebob;
    cout << ekok << endl;
    cout << ebob;
}
