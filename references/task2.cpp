#include <iostream>
#include <algorithm>
using namespace std;

int& minRef(int arr[], int size)
{
    if (size<=0)
    {
        static int error = 0;
        cout << "Размер не может быть меньше или равен нулю";
        return error;
    }
    
    int minIndex = 0;

    for (int i = 1; i < size; i++)
    {
        if (arr[i] < arr[minIndex])
        {minIndex = i;}
    }

    return arr[minIndex];

}

int& maxRef(int arr[], int size)
{
    if (size<=0)
    {
        static int error = 0;
        cout << "Размер не может быть меньше или равен нулю";
        return error;
    }
    
    int maxIndex = 0;

    for (int i = 1; i < size; i++)
    {
        if (arr[i] > arr[maxIndex])
        {maxIndex = i;}
    }

    return arr[maxIndex];

}

void normalize(int arr[], int size)
{
    int& max = maxRef(arr, size);
    int& min = minRef(arr, size);
    max = 100;
    min = 0;
}

int main()
{
    int test_arr[] = {42, 17, 89, 3, 56, 21, 74, 8, 95, 12, 63, 30, 47, 5, 88};
    int test_size = sizeof(test_arr) / sizeof(test_arr[0]);
    normalize(test_arr, test_size);
    cout << "Максимальный элемент массива: " << maxRef(test_arr, test_size) << endl;
    cout << "Максимальный элемент массива: " << minRef(test_arr, test_size);
}