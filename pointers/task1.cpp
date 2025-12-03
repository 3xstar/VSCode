#include <iostream>
using namespace std;

int main(){
    int x = 5;
    int* p = &x;
    cout << "Ссылка на x: " << p << "\nЗначение x: " << *p;
    *p = 10;
    cout << "\nx с новым значением: " << x;
}