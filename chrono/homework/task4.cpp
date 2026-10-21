#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <array>

using namespace std;

int sumRecursive(int n) {
    if (n <= 0) return 0;
    
    return n + sumRecursive(n - 1);
}


int sumIterative(int n) {
    int total = 0;
    for (int i = 1; i <= n; i++) {
        total += i;
    }
    return total;
}


int main(){
    const int number = 40000;

    cout << "Сравнение скорости рекурсивной и итеративной функций" << endl;
    auto recursive_in = chrono::steady_clock::now();
    sumRecursive(number);
    auto recursive_out = chrono::steady_clock::now();
    auto recursive_duration = recursive_out - recursive_in;


    auto iterative_in = chrono::steady_clock::now();
    sumIterative(number);
    auto iterative_out = chrono::steady_clock::now();
    auto iterative_duration = iterative_out - iterative_in;


    auto rec_time = chrono::duration_cast<chrono::milliseconds>(recursive_duration);
    auto iter_time = chrono::duration_cast<chrono::milliseconds>(iterative_duration);
    cout << "Затраченное время на выполнение рекурсивной функции составляет: " << rec_time.count() << "ms." << endl;
    cout << "Затраченное время на выполнение итеративной функции составляет: " << iter_time.count() << "ms." << endl;
}