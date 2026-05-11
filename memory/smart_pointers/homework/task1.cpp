#include <iostream>
#include <memory>

using namespace std;

int main(){
    int number = 67;
    unique_ptr<int> ptr(new int(number));
    cout << "Unique ptr value: " << *ptr;
}