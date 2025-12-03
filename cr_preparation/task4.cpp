#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

void quickSort(vector<int> &arr, int left, int right) {
	int i = left, j = right;
	int pivot = arr[(left + right) / 2];
	while (i <= j) {
		while (arr[i] < pivot) i++;
		while (arr[j] > pivot) j--;
		if (i <= j) swap(arr[i++], arr[j--]);
	}

	if (left < j) quickSort(arr, left, j);
	if (i < right) quickSort(arr, i, right);
}

void showMenu() {
    cout << "\n=== МЕНЮ ===" << endl;
    cout << "1. Генерация случайного массива" << endl;
    cout << "2. Сортировка массива" << endl;
    cout << "3. Вывод массива" << endl;
    cout << "4. Поиск минимума/максимума" << endl;
    cout << "5. Выход" << endl;
    cout << "Выберите операцию: ";
}

int main()
{
    srand(time(0));
    vector <int> arr = {rand(), rand(), rand(), rand(), rand()};
    int choise;

    do {
        showMenu();
        cin >> choise;

        switch(choise) {
            case 1:
                cout << "Массив из рандомных чисел: ";
                for (int num : arr) {
                    cout << num << " ";
                }
                cout << endl;
                break;


            case 2:
                quickSort(arr, 0, arr.size() - 1);

                cout << "Массив отсортирован: ";
                for (int num : arr) {
                    cout << num << " ";
                }
                cout << endl;
                break;


            case 3:
                cout << "Итоговый массив: ";
                for (int num : arr) {
                    cout << num << " ";
                }
                cout << endl;
                break;

            
            case 4: {
                int min_num = arr[0];
                int max_num = arr[0];

                for (int i = 1; i < arr.size(); i++) {
                    if (arr[i] < min_num) {
                        min_num = arr[i];
                    }
                    if (arr[i] > max_num) {
                        max_num = arr[i];
                    }
                }

                cout << "Минимальное значение: " << min_num << endl;
                cout << "Максимальное значение: " << max_num << endl;
                break;
            }
            

            case 5:
                cout << "Выход из программы...";
                break;


            default:
                cout << "Неверный выбор! Попробуйте снова." << endl;
                break;

        }
    }
    while (choise != 5);
    return 0;
}