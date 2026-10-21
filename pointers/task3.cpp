#include <iostream>
using namespace std;

int main(){
    int arr[3] = {5, 10, 15};
    int n = sizeof(arr) / sizeof(arr[0]);
    int *max = arr;

    for (int i=1; i < n; i++)
    {
        if (arr[i] > *max){
            max = &arr[i];
        }
    }
    cout << "Прошлое значение последнего элемента: " << *max;
    *max = 50;
    cout << "\nНовое значение последнего элемента: " << *max;
}