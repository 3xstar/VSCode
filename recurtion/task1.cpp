#include <iostream>
using namespace std;

int sumEvenIndex(const int arr[], int size) {
    if (size <= 0)
        return 0; // базовый случай
    return arr[0] + sumEvenIndex(arr + 2, size - 2); // берём элемент и прыгаем через один
}

int main() {
    int data[] = {1, 2, 3, 4, 5, 6};
    cout << sumEvenIndex(data, 6); // результат: 9 (1 + 3 + 5)
}