#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void delete_even_numbers(vector<int>& test){
    test.erase(remove_if(test.begin(), test.end(), [](int x){
        return x % 2 == 0;
    }), test.end());
}

int main(){
    vector<int> numbers = {1,2,3,4,5};

    cout << "Вектор: ";
    for_each(numbers.begin(), numbers.end(), [](int x){
        cout << x << " ";});

    delete_even_numbers(numbers);
    
    cout << endl << "Вектор без четных чисел: ";
    for_each(numbers.begin(), numbers.end(), [](int x){
        cout << x << " ";});
}