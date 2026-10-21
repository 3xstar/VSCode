#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <array>

using namespace std;


int main(){
    int arr[100000] {};

    cout << "Сравнение скорости сортировок sort и bubble" << endl;

    auto sort_in = chrono::steady_clock::now();
    sort(begin(arr), end(arr));
    auto sort_out = chrono::steady_clock::now();
    auto sort_duration = sort_out - sort_in;


    int arr2[100000] {};

    auto bubble_in = chrono::steady_clock::now();
    int s = size(arr2);
    for(int i=0; i < s; i++){
        for(int j=0; j < s - 1 - i; j++){
            if (arr2[j] > arr2[j + 1]){
                swap(arr2[j], arr2[j + 1]);
            }
        }
    }
    auto bubble_out = chrono::steady_clock::now();
    auto bubble_duration = bubble_out - bubble_in;


    auto sort_time = chrono::duration_cast<chrono::milliseconds>(sort_duration);
    auto bubble_time = chrono::duration_cast<chrono::milliseconds>(bubble_duration);
    cout << "Затраченное время на выполнение sort составляет: " << sort_time.count() << "ms." << endl;
    cout << "Затраченное время на выполнение bubble sort составляет: " << bubble_time.count() << "ms." << endl;
}