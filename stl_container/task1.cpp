#include <vector>
#include <iostream>
using namespace std;

int main()
    {
        int n;
        cout << "Введите количество чисел до n: ";
        cin >> n;
        vector<int> vec_n = {};
        
        if (n > 0){
            for (int i = 0; i < n; i++) {
            vec_n.push_back(i);
            }
        }

        for(int num : vec_n){
            cout << num << "";
        }
        
        return 0;
    }