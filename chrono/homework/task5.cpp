#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <array>

using namespace std;

long long arraySort(vector<int> arr){
    auto time_in = chrono::steady_clock::now();
    sort(arr.begin(), arr.end());
    auto time_out = chrono::steady_clock::now();
    auto duration = time_out - time_in;
    auto ms = chrono::duration_cast<chrono::milliseconds>(duration); 
    cout << "Затраченное время на выполнение сортировки массива составляет: " << ms.count() << "ms." << endl;
    return ms.count();
}

int main(){
    const int SIZE = 10000000;
    vector<int> arr(SIZE);
    for(int i = 0; i < SIZE; i++){
        arr[i] = i + 1;
    }
    int target = SIZE;
    

    cout << "Вычисление среднего времени за 5 запусков программы" << endl;

    cout << "1 - Сортировка массива из 100000 элементов" << endl;
    long long time1 = arraySort(arr);


    cout << "2 - Сортировка массива из 100000 элементов" << endl;
    long long time2 = arraySort(arr);

    
    cout << "3 - Сортировка массива из 100000 элементов" << endl;
    long long time3 = arraySort(arr);
    

    cout << "4 - Сортировка массива из 100000 элементов" << endl;
    long long time4 = arraySort(arr);
    

    cout << "5 - Сортировка массива из 100000 элементов" << endl;
    long long time5 = arraySort(arr);


    long long mid_time = (time1 + time2 + time3 + time4 + time5)/5;
    cout << "Среднее время выполнения: " << mid_time;
}
