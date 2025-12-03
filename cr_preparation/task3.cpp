#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

int main() {
    int randNum = rand();
    int randNum2 = rand();
    int randNum3 = rand();
    int randNum4 = rand();

    vector <int> sigma = {randNum, randNum2, randNum3, randNum4};

    cout << "Рандомные числа из вектора: ";
    for (auto item : sigma) cout << "\n" << item;

    return 0;
}