#include <iostream>
#include <stdexcept>

using namespace std;

int division(int a, int b){
    if(b == 0){
        throw runtime_error("На ноль делить нельзя!");
    }
    return a/b;
}

int main(){
    int x = 10;
    int y = 5;
    try{
        cout << division(x, y);
    }
    catch(const runtime_error& e){
    cout << "Ошибка: " << e.what() << endl;
    }
}