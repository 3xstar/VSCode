#include <iostream>
using namespace std;

int main()
{
    int inch = 10;
    float cm = inch * 2.54;
    cout << inch << " дюймов в сантиметрах равно: " << cm << endl;

    int pet_food_count = 3;
    short days = 7;
    cout << "Если питомец съедает за день " << pet_food_count << " миски, то через " << days << " дней он съест: " << pet_food_count*days << endl;

    string name1 = "Андрей";
    string name2 = "Вадим";
    string name3 = "Никита";

    string gift1 = "Автомобиль";
    string gift2 = "Стринги";
    string gift3 = "Купленный военный билет";
    cout << name1 << " получит в будущем: " << gift1 << endl;
    cout << name2 << " получит в будущем: " << gift2 << endl;
    cout << name2 << " получит в будущем: " << gift3 << endl;
}

/*
    Задание 1.
    Приложение для конвертации дюймов в сантиметры

    Задание 2.
    Есть домашний питомец, который каждый день съедает определенное количество корма
    сколько корма он съест за указанное количество дней

    Задание 3.
    Симуляция выдачи подарков, определенному имени определенный подарок
*/
