#include <iostream>
#include <vector>
#include <string>
using namespace std;

void quickSortByLength(vector<string>& arr, int left, int right) {
    int i = left, j = right;
    int pivot = arr[(left + right) / 2].size(); // сравниваем по длине

    while (i <= j) {
        while (arr[i].size() < pivot) i++;
        while (arr[j].size() > pivot) j--;
        if (i <= j) swap(arr[i++], arr[j--]);
    }

    if (left < j) quickSortByLength(arr, left, j);
    if (i < right) quickSortByLength(arr, i, right);
}

int main() {
    vector<string> words = {"cat", "elephant", "dog", "rabbit", "fox"};
    quickSortByLength(words, 0, words.size() - 1);
    for (string w : words) cout << w << " "; // результат: cat dog fox rabbit elephant
}