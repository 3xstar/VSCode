#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    setlocale(LC_ALL, "ru");

    string word;
    cout << "Введите слово: ";
    cin >> word;

    string reversed = word;
    reverse(reversed.begin(), reversed.end());

    if (word == reversed)
    {
        cout << "Строка является палиндромом" << endl;
    }
    else
    {
        cout << "Строка не является палиндромом" << endl;
    }
    system("pause");
    return 0;
}