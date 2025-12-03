#include <iostream>

int main()
{
    int speed = 50; // Скорость
    bool card = true; // Наличие водительских прав
    bool money_give = 5000; // Взятка

    if ((card && speed < 90) || money_give >= 5000) {
        std::cout << "Не получаешь штраф";
    }

    else if ((card = false && speed >= 90) || money_give < 5000) {
        std::cout << "Выписываем штраф";
    }

    // Второй пример
    // Условия автомата:
    // 1. Средний балл выше 4.8, 80% посещаемость
    // или
    // 2. Если является старостой или активистом

    float avg = 4.35;
    int attedance = 75;
    bool activity, general;
    std::cout << "Введите 0, если вы не активист\n Введите любое друго число если вы активист";
    std::cin >> activity;
    std::cout << "Введите 0, если вы не староста\n Введите любое друго число если вы староста";
    std::cin >> general;

    if ((avg > 4.8 && attedance >= 80) || (activity || general)) {
        std::cout << "Ты получаешь автомат";
    }

    else {
        std::cout << "Ты лишен автомата";
    }
}