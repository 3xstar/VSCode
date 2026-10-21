#include <iostream>
#include <algorithm>
using namespace std;

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

int main()
{
    int test_arr[] = {1,4,3,5,2};
    int test_size = sizeof(test_arr) / sizeof(test_arr[0]);
    int& test_maxRef = maxRef(test_arr, test_size);
    cout << "Максимальный элемент массива: " << test_maxRef << endl;
    test_maxRef = 100; // Проверка на изменение (ссылки могут изменятся)
    cout << "Новый максимальный элемент массива: " << test_maxRef;
}