#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
    {
        string text;
        cout << "Введите текст для удаления цифр: ";
        getline(cin, text);
        string result;

        for(char c : text) {
            if(!isdigit(c)) {
                result += c;
            }
        }

        cout << "Полученный текст" << endl;
        cout << result;

        return 0;
    }
