#include <iostream>
using namespace std;

int arr[] = {1,2,3,4,5};
int sz = sizeof(arr)/sizeof(arr[0]);

void arr_func(int* arr, int size){
    for(int i=0; i < size; i++){
        arr[i] += 10;
        cout << arr[i] << endl;
    }
};

int main()
{
    cout << "Массив с числами += 10:" << endl;
    arr_func(arr, sz);
};