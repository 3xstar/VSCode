#include <iostream>
using namespace std;


void apply(int* arr, int size, int(*operation)(int)){
    for(int i=0; i<size; i++){
        arr[i] = operation(arr[i]);
        cout << arr[i] << endl;
    }
};

int square(int x){
    return x *= x;
};

int invert(int x){
    return -x;
};

int main(){
    int test_arr[] = {1, 2, 3, 4, 5};
    int test_arr2[] = {1, 2, 3, 4, 5};
    int sz = sizeof(test_arr)/sizeof(test_arr[0]);
    cout << "Возведение в квадрат:" << endl;
    apply(test_arr, sz, square);
    cout << "\n";
    cout << "Смена знака:" << endl;
    apply(test_arr2, sz, invert);
};