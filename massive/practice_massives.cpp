#include <iostream>
using namespace std;

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int count = sizeof(arr) / sizeof(arr[0]);
    int sum = 0;
    
    for (int i = 0; i < count; i++) {
        sum += arr[i];
    }
    
    cout << "Сумма: " << sum << endl;


    int arr2[] = {1, 2, 3, 4, 5};
    int count2 = sizeof(arr2) / sizeof(arr2[0]);
    int sum2 = 0;

    for (int i = 0; i < count2; i++) {
        sum2 += arr2[i];
    }

    int average_number = sum2/count2;

    cout << "Среднее значение: " << average_number << endl;


    int arr3[] = {1, 2, 3, 4, 5};
    int count3 = sizeof(arr3) / sizeof(arr3[0]);
    cout << "Минимальное значение: " << arr3[0] << endl;
    cout << "Максимальное значение: " << arr3[count3-1] << endl; 


    int arr4[] = {5, 1, 2, 4, 3};

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4 - i; j++)
            if (arr4[j] > arr4[j + 1])
                std::swap(arr4[j], arr4[j + 1]);
                std::cout << "Отсортированный массив: ";
                for (int i = 0; i < 5; i++) {
                    std::cout << arr4[i] << " ";}

    return 0;
}