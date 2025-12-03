#include <iostream>
#include <vector>
using namespace std;

int countOccurrences(const vector<int>& arr, int left, int right, int x) {
    if (left > right)
        return 0; // базовый случай
    
    int mid = (left + right) / 2;
    
    if (arr[mid] == x) {
        // Нашли число, считаем в обе стороны
        int count = 1;
        
        // Ищем слева
        int leftPos = mid - 1;
        while (leftPos >= left && arr[leftPos] == x) {
            count++;
            leftPos--;
        }
        
        // Ищем справа
        int rightPos = mid + 1;
        while (rightPos <= right && arr[rightPos] == x) {
            count++;
            rightPos++;
        }
        
        return count;
    }
    else if (arr[mid] < x) {
        return countOccurrences(arr, mid + 1, right, x);
    }
    else {
        return countOccurrences(arr, left, mid - 1, x);
    }
}

int main() {
    vector<int> data = {1, 2, 2, 2, 3, 4, 5};
    int x = 2;
    cout << countOccurrences(data, 0, data.size() - 1, x); // результат: 3
}