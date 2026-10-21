#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(){
    ifstream fin("numbers.txt");
    vector<int> nums;
    int n;

    cout << "Числа в numbers.txt:" << endl;
    while(fin >> n){
        cout << n << " ";
        nums.push_back(n);
    }

    cout << endl;
    
    int sum = 0;
    for(int num : nums){
        sum += num;
    }

    int mid_numb = sum / nums.size();
    cout << "Среднее значение чисел из numbers.txt: " << mid_numb; 
}