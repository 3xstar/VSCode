#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
    {
        string text;
        cout << "Введите текст для вычисления пробелов: ";
        getline(cin, text);

        int space_count = count(text.begin(), text.end(), ' ');

        cout << "Количество пробелов: ";
        cout << space_count;

        return 0;
    }
