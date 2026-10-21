#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <array>

using namespace std;

int binarySearch(const vector<int>& arr, int left, int right, int target) {
	if (left > right) return -1;
	int mid = left + (right - left) / 2;
	if (arr[mid] == target) return mid;
	else if (arr[mid] > target) return binarySearch(arr, left, mid - 1, target);
	else return binarySearch(arr, mid + 1, right, target);
  
}

int linearSearch(const vector<int>& arr, int target) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

int main(){
    const int SIZE = 100000000;
    vector<int> arr(SIZE);
    for(int i = 0; i < SIZE; i++){
        arr[i] = i + 1;
    }
    int target = SIZE;

    cout << "Сравнение скорости binary search и linear search" << endl;
    auto binary_in = chrono::steady_clock::now();
    binarySearch(arr, 0, arr.size() - 1, target);
    auto binary_out = chrono::steady_clock::now();
    auto binary_duration = binary_out - binary_in;


    auto linear_in = chrono::steady_clock::now();
    linearSearch(arr, target);
    auto linear_out = chrono::steady_clock::now();
    auto linear_duration = linear_out - linear_in;


    auto binary_time = chrono::duration_cast<chrono::milliseconds>(binary_duration);
    auto linear_time = chrono::duration_cast<chrono::milliseconds>(linear_duration);
    cout << "Затраченное время на выполнение binary search составляет: " << binary_time.count() << "ms." << endl;
    cout << "Затраченное время на выполнение linear search составляет: " << linear_time.count() << "ms." << endl;
}