#include <iostream>
#define MIN(x, y) ((x) > (y) ? x : y) // Создаем макрос
using namespace std;

template <typename minValue>
void function(minValue x, minValue y){
    if (x > y) {
        cout << "X > Y";
    }
    if (y > x) {
        cout << "Y > X";
    }
}

int main(){
    cout << MIN(5, 6) << endl;
    function(6, 5);
}