#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
    {
        string text;
        cout << "Введите текст для замены пробелов: ";
        getline(cin, text);

        for (int i = 0; i < text.length(); i++) {
        if (text[i] == ' ') {
            text[i] = '_';
            }
        }
        
        cout << "Полученный текст" << endl;
        cout << text;

        return 0;
    }
