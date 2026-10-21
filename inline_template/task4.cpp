#include <iostream>
using namespace std;

template <typename T>
void swapValues(T& a, T& b) {
    T save = a;
    a = b;
    b = save;

    cout << "A = " << a << " B = " << b;
}

int main() {
    int a = 10;
    int b = 20;
    swapValues(a, b);
}