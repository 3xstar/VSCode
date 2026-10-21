#include <iostream>

int main()
{
    short years;
    short months;
    short days;
    std::cout << "Введите год (1900-2100):\n";
    std::cin >> years;
    std::cout << "Введите месяц (1-12):\n";
    std::cin >> months;
    std::cout << "Введите день (1-31):\n";
    std::cin >> days;
    if (years < 1900 || years > 2100) {
        std::cout << "Вы ввели неккоректный год";
    }
    else {
        if (months < 1 || months > 12) {
            std::cout << "Вы ввели неккоректный месяц";
        }
        else {
            if (days < 1 || days > 31) {
                std::cout << "Вы ввели неккоректный день";
            }
            else {
                if (months = 1 && days > 29) {}
            }

        }

    }
}