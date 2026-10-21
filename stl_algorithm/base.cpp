#include <iostream>
#include <vector>
#include <algorithm>  // подключаем алгоритмы
#include <string>

using namespace std;

int main() {
    setlocale(LC_ALL, "ru");

    vector<int> v = {5, -3, 2, -1, 4, 0, -7};
    
    // ==================== Сортировка ====================
    sort(v.begin(), v.end());  // сортировка по возрастанию
    // sort(v.rbegin(), v.rend());  // сортировка по убыванию

    // ==================== Поиск ====================
    auto it = find(v.begin(), v.end(), 4);
    if (it != v.end()) {
        cout << "Элемент 4 найден" << endl;
    } else {
        cout << "Элемент 4 не найден" << endl;
    }

    // ==================== Поиск по условию ====================
    auto it_if = find_if(v.begin(), v.end(), [](int x) {
        return x < 0;
    });
    if (it_if != v.end()) {
        cout << "Первый отрицательный элемент: " << *it_if << endl;
    }

    // ==================== Подсчёт ====================
    int cnt = count(v.begin(), v.end(), -1);
    cout << "Число -1 встречается " << cnt << " раз" << endl;

    // ==================== Подсчёт по условию ====================
    int cnt_if = count_if(v.begin(), v.end(), [](int x) {
        return x % 2 == 0;
    });
    cout << "Чётных чисел: " << cnt_if << endl;

    // ==================== Проверка всех/любого/ни одного ====================
    bool all_pos = all_of(v.begin(), v.end(), [](int x) { return x > 0; });
    bool any_neg = any_of(v.begin(), v.end(), [](int x) { return x < 0; });
    bool none_zero = none_of(v.begin(), v.end(), [](int x) { return x == 0; });

    // ==================== Минимум и максимум ====================
    auto min_it = min_element(v.begin(), v.end());
    auto max_it = max_element(v.begin(), v.end());
    if (min_it != v.end()) {
        cout << "Минимум: " << *min_it << endl;
    }
    if (max_it != v.end()) {
        cout << "Максимум: " << *max_it << endl;
    }

    // ==================== Преобразование (transform) ====================
    vector<int> doubled(v.size());
    transform(v.begin(), v.end(), doubled.begin(), [](int x) {
        return x * 2;
    });

    // ==================== Копирование ====================
    vector<int> copy_v(v.size());
    copy(v.begin(), v.end(), copy_v.begin());

    // ==================== Удаление (remove + erase) ====================
    v.erase(remove_if(v.begin(), v.end(), [](int x) {
        return x % 2 == 0;  // удаляем чётные
    }), v.end());

    // ==================== for_each ====================
    for_each(v.begin(), v.end(), [](int x) {
        cout << x << " ";
    });
    cout << endl;

    // ==================== Работа со строками ====================
    string s = "hello";
    sort(s.begin(), s.end());  // "ehllo"
    // sort(s.rbegin(), s.rend());  // обратный порядок

    return 0;
}