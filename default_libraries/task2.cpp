#include <iostream>
#include <vector>

using namespace std;

int main(){
    vector<int> numbers = {4, 3, 2, 1, 5};

    cout << "Вектор: ";
    for (auto& i : numbers){
        cout << i << " ";
    }

    int first_max = 0;
    int second_max;

    for(auto& i : numbers){
        if(i > first_max){
            second_max = first_max;
            first_max = i;
        }
    }

    cout << endl << "Второй по величине элемент из вектора: " << second_max;

}
