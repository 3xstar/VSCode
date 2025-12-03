#include <iostream>
#define ADD(a, b) ((a) + (b)) // Создаем макрос
using namespace std;

template <typename T>
T print_type(T t) {
    return t;
}

template <typename K, typename V>
void get(K k, V v) {
    cout << "Key = " << k << " Value: " << v << endl;
}
// Пример использования inline
inline void print(){
    cout << "Какое-то сообщение" << endl;
}

// Пример использования inline
inline int sum(int a = 2, int b = 4) {
    return a + b;
}

int main()
{
    // Макрос - тестовая вставка, выполняемая для компиляции

    print();
    cout << sum() << endl;
    cout << ADD(2, 3) << endl; // a + b
    cout << ADD(2, 3) * 2 << endl; // a + b * 2, а надо (a + b) * 2

    // Демонстрация работы шаблона
    cout << print_type(21) << " - это число" << endl;
    cout << print_type(21.4) << " - это дробь" << endl;
    cout << print_type("Text") << " - это строка" << endl;
    cout << print_type(true) << " - это логическое значение" << endl;
    get("Возраст", 21);

    // Бонус: Тернарный оператор
    int a = 10, b = 12;
    bool check = a > b ? true : false;
    int check_int = a > b ? a : b;
    int result = a > b ? a > 0 ? a : -a : b > 0 ? b : -b; // Тяжело

    // Переписываем пример с 44 строчки
    if (a > b) {
        if (a > 0) {
            cout << a;
        }
        else {
            cout << -a;
        }
    }

    else {
        if (b > 0) {
            cout << b;
        }
        else {
            cout << -b;
        }
    }

    int ball;
    cin >> ball;
    char score = ball > 80 && ball < 100 ? 'A'
        : ball < 80 && ball > 60 ? 'B'
        : ball < 60 && ball > 40 ? 'C' 
        : ball < 40 ? 'D' : 'N';

    if (ball > 80 && ball < 100) {
        cout << "A";
    }

    else {
        if (ball < 80 && ball > 60) {
            cout << "B";
        }

        else {
            if (ball < 60 && ball > 40) {
                cout << "C";
            }

            else {
                if (ball < 40) {
                    cout << "D";
                }

                else {
                    cout << "N";
                }

            }
        }

    }
}

