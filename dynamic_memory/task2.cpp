#include <iostream>
using namespace std;

int* createArray(int n){
    return new int[n];
}

int main()
{
    int* arr = createArray(10);
    int sum = 0;

    for(int i=0; i < 10; i++)
    {
        arr[i] = i + 1;
        sum += arr[i];
    }
    cout << "Сумма элементов массива: " << sum;
    
    delete[] arr;
}