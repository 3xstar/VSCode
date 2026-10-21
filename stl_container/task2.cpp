#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
    {
        vector<int> vec_n = {};

        int a;
        cout << "Введите первое число: ";
        cin >> a;

        int b;
        cout << "Введите второе число: ";
        cin >> b;

        int c;
        cout << "Введите третье число: ";
        cin >> c;
        
        vec_n.push_back(a);
        vec_n.push_back(b);
        vec_n.push_back(c);

        cout << "Исходный вектор: ";
        for(int num : vec_n){
            cout << num;
        }

        vec_n.erase(remove(vec_n.begin(), vec_n.end(), 0),
        vec_n.end()
        );

        cout << endl << "Новый вектор без нулей: ";
        for(int num : vec_n){
            cout << num;
        }
        
        return 0;
    }