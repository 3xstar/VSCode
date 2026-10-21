#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int main(){

    //Основные функции:
    //accumulate - Суммирование элементов диапозона
    //iota - Заполнение контейнера последовательными числами
    //partial_sum - Считает префиксные суммы 

    //Пример accumulate
    vector <int> v = {1, 2, 3, 4, 5};
    int sum = accumulate(v.begin(), v.end(), 0); // 0 - начальное значение
    cout << "Сумма всех элементов вектора v = " << sum << endl;

    //Пример iota
    vector<int> v2(10);
    iota(v2.begin(), v2.end(), 1);
    cout << "Заполненный вектор: ";
    for (int x : v2){
        cout << x << " ";
    }

    //Пример partial_sum
    vector<int> res(v2.size());
    partial_sum(v2.begin(), v2.end(), res.begin());
    cout << endl << "Вектор после подсчета префиксных сумм: ";
    for(int x : res) cout << x << " ";

}