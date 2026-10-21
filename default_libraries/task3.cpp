#include <iostream>
#include <algorithm>

using namespace std;

string sort_function(string test){
    sort(test.begin(), test.end());
    return test;
}

int main(){
    string letters;
    cout << "Введите буквы на английском для сортировки: ";
    cin >> letters;

    string sort_letters = sort_function(letters);

    cout << endl << "Отсортированный результат: " << sort_letters;
}

// У МЕНЯ РУССКИЙ ВООБЩЕ НЕ РАБОТАЕТ ЛЮБЫМИ СПОСОБАМИ