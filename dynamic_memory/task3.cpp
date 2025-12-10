#include <iostream>
using namespace std;

int* createArray(int n){
    int* arr = new int[n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = i + 1;
    }
    return arr;
}

int main()
{
    int n = 10;
    int* arr = createArray(n);
    int* newarr = new int[n - 1];
    int j = 0;

    cout << "Исходный массив:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << arr[i];
    }

    for (int i = 0; i < n; i++)
    {
        if(arr[i] == 5)
        {
            arr[i] = 0;
        }
    }

    for (int i = 0; i < n; i++)
    {
        if(arr[i] != 0)
        {
            newarr[j] = arr[i];
            j++;
        }
        else{continue;}
    }

    delete[] arr;

    arr = newarr;
    
    cout << endl << "Перезаписанный с удаленным элементом массив:" << endl;
    for (int i = 0; i < n-1; i++)
    {
        cout << arr[i];
    }
    
    delete[] arr;
}