#include <iostream>
using namespace std;

int counter(int count) {
    static int x = 5;
    int result = x + count;
    count = result;
    return count;
}

int main(){
    int a = 10;
    cout << "A with counter = " << counter(a);
}