#include <iostream>
using namespace std;

int arr[] = {1,2,3,4,5};
int sz = sizeof(arr)/sizeof(arr[0]);

int* reverse_arr(int* arr, int size){
    int* new_arr = new int[size];

    for(int i=0; i < size; i++){
        new_arr[i] = arr[size - 1 - i];
    }
    return new_arr;
};

int main()
{
    cout << "Новый массив с обратным порядком: " << endl;
    int* reversed = reverse_arr(arr, sz);
    for(int i=0; i < sz; i++){
        cout << reversed[i] << endl;
    }

    delete reversed;
};