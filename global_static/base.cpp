#include <iostream>
using namespace std;

int val = 10;

void get_val() {
    cout << val << endl;
}

int numb(int& b) {
    b = 21;
    cout << b << endl;
    return b;
}

void counter() {
    static int a = 0;
    a++;
    cout << "Variable a: " << a << endl;
}

int main()
{
    setlocale(LC_ALL, "");

    // 1. Получение знамения переменной напрямую
    cout << "Global variable: " << val << endl;

    // 2. Получение значения переменной через блок
    if (1 < 2) {
        cout << "Through block: ";
        val = 12;
    }

    // 3. Получение значения переменной через функцию
    get_val();

    counter();
    counter();
    counter();

    /*
        Статическая область видимости

        Статическая область у блока
    */


    // Использование ссылки
    // Ссылочная переменная передает свое значение переменной d
    int d = 10;
    cout << numb(d);
}
