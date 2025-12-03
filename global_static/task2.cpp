#include <iostream>
#include <array>
using namespace std;

array <int, 2> swap(int &x, int&y) {
    int temp = x;
    x = y;
    y = temp;
    return {x, y};
}

int main(){
    int a = 10;
    int b = 20;
    auto result = swap(a, b);
    cout << "a = " << a << endl << "b = " << b;
}