#include <iostream>
using namespace std;

int countDigits(int n) {
    if (n == 0)
        return 0; // базовый случай
    return 1 + countDigits(n / 10); // убираем последнюю цифру и считаем
}

int main() {
    int num = 12345;
    cout << countDigits(num); // результат: 5
}