#include <iostream>
#include <vector>
using namespace std;

void quickSortDesc(vector<int>& arr, int left, int right) {
    int i = left, j = right;
    int pivot = arr[(left + right) / 2];

    while (i <= j) {
        while (arr[i] > pivot) i++; // поменяли знак сравнения
        while (arr[j] < pivot) j--; // поменяли знак сравнения
        if (i <= j) swap(arr[i++], arr[j--]);
    }

    if (left < j) quickSortDesc(arr, left, j);
    if (i < right) quickSortDesc(arr, i, right);
}

int main() {
    vector<int> data = {10, 7, 2, 8, 6, 1, 5};
    quickSortDesc(data, 0, data.size() - 1);
    for (int x : data) cout << x << " "; // результат: 10 8 7 6 5 2 1
}