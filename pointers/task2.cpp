#include <iostream>
using namespace std;

int main(){
    int arr[3] = {5, 10, 15};
    int* arr2 = arr;
    int sum = 0;
    for (int i=0; i < 3; i++)
    {
        sum += *(arr2 + i);
    }
    cout << "Сумма элементов массива: " << sum;
}