#include <iostream>
#include <vector>
using namespace std;

int sum(const vector<int>&numbers){
    int sum = 0;
    for(int i = 0; i < numbers.size(); i++){
        sum += numbers[i];
    }
    return sum;
}

int main(){
    vector <int>arr = {10, 20, 30, 40};
    cout << "Sum of vector: " << sum(arr);
}