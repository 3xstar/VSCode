#include <iostream>
#include <vector>
using namespace std;

int minArray(){
    int arr[] = {1, 2, 3, 4, 5};
    cout << "Минимальное значение: " << arr[0] << endl;
    return arr[0];
}

int main(){
    minArray();
}