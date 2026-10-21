#include <vector>
#include <iostream>
using namespace std;

int main()
    {
        vector <double> numbers;
        double num;

        cout << "Введите числа через пробел: ";

        while (cin >> num) {
            numbers.push_back(num);
            if (cin.peek() == '\n') break;
        }

        double sum = 0;
        int num_count = 0;

        for (char c : numbers){
            sum += c;
            num_count += 1;
        }

        double middle_number = sum / num_count;

        cout << "Сумма чисел: " << sum << endl;
        cout << "Среднее значение чисел: " << middle_number;

        return 0;
    }