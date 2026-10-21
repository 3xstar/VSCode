#include <iostream>
#include <vector>

using namespace std;

/*
Синтаксис:
<тип_возвращаемых_данных><название_функции>(<список_параметров>)
{
тело функции
}
*/
int a = 10;
int sum(int &a, int b) {
    return a + b;
}

double sum(double a, double b){
    return a + b;
}

string sum(string a, string b){
    return a + b;
}

void main() {
    cout << sum(10, 12);
}