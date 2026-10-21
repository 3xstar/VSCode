#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    vector<int> numbers = {-5, 9, 4, -3, 7, 2, 8, -1};

    cout << "Исходный вектор: ";
    for (auto& i : numbers){
        cout << i << " ";
    }
    
    numbers.erase(remove_if(numbers.begin(), numbers.end(), 
    [](int x) {return x < 0;}), numbers.end());

    cout << endl << "Новый вектор без отрицательных чисел: ";
    for (auto& i : numbers){
        cout << i << " ";
    }
}