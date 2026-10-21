#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <array>

using namespace std;


int main(){
    int arr[100000] {};

    cout << "Сортировка массива из 100000 элементов" << endl;
    auto time_in = chrono::steady_clock::now();
    sort(begin(arr), end(arr));
    auto time_out = chrono::steady_clock::now();
    auto duration = time_out - time_in;

    auto ms = chrono::duration_cast<chrono::milliseconds>(duration); 
    cout << "Затраченное время на выполнение сортировки массива составляет: " << ms.count() << "ms." << endl;
}
