#include <vector>
#include <iostream>
using namespace std;

int main()
    {
        vector <int> numbers;
        int num;

        cout << "Введите числа через пробел: ";

        while (cin >> num) {
            numbers.push_back(num);
            if (cin.peek() == '\n') break;
        }

        int sum = 0;
        int num_count = 0;
        int more_than_middle = 0;

        for (char c : numbers){
            sum += c;
            num_count += 1;
        }

        double middle_number = sum / num_count;

        for (char c : numbers){
            if (c > middle_number){
                more_than_middle += 1;
            }
        }

        cout << "Среднее значение чисел: " << middle_number << endl;
        cout << "Количество чисел из вектора, которые больше среднего значения: " << more_than_middle;

        return 0;
    }