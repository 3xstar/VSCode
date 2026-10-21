#include <iostream>
using namespace std;

int increment(int &x) {
    x++;
    return x;
}

int main(){
    int a = 1;
    cout << "A with increment = " << increment(a);
}