#include <iostream>
#include <vector>
#include <array>

using namespace std;

int main()
{
    setlocale(LC_ALL, "ru");
    string name = "Text";
    cout << name[3] << endl;

    cout << "Длина строки: " << name.size() << endl;
    cout << "Наличие подстроки: " << name.find("xt") << endl;
    if (name.find("xt") > name.size()) {
        cout << "Такой подстроки нету" << endl;
    }

    else{
        cout << "Строка есть" << endl;
    }

    array<int, 10> arr = {1,2,3,4,5,6,7,8,9,10};
    arr.fill(10);

    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " " << endl;
    }

    vector <string> rows = {"Текст 1", "Текст 2", "Текст 3"};

    rows.push_back("Текст 4");

    for (auto item : rows) cout << "\n" << item;
    for (auto item : arr) cout << "\n" << item;
    for (auto item : name) cout << "\n" << item;
}