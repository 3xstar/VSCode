#include <iostream>
using namespace std;

int* createArray(int n){
    return new int[n];
}

int main()
{
    int* arr = createArray(10);

    cout << "Элементы массива:" << endl;
    for(int i=0; i < 10; i++)
    {
        arr[i] = i + 1;
        cout << arr[i];
    }
    
    delete[] arr;
}