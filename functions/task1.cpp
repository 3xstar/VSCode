#include <iostream>
using namespace std;

double square() {
    double x;
    cout << "Введи число для вычисления квадрата: ";
    cin >> x;
    double square_x = x * x;
    cout << "Квадрат числа: " << x << " = " << square_x;
    return square_x;
}

int main(){
    square();
}

