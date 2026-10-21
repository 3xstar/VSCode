#include <iostream>
using namespace std;

inline int cube(int x){
    return x * x * x;
}

int main() {
    cout << cube(4);
}