#include <iostream>
#include <vector>
using namespace std;

bool isPrime() {
    int n;
    cout << "Введите число для определения: ";
    cin >> n;

    if (n <= 1) {
        cout << "Число " << n << " не является простым" << endl;
        return false;
    }

    if (n <= 3) {
        cout << "Число " << n << " является простым" << endl;
        return true;
    }

    if (n % 2 == 0 || n % 3 == 0) {
        cout << "Число " << n << " не является простым" << endl;
        return false;
    }

    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            cout << "Число " << n << " не является простым" << endl;
            return false;
        }
    }

    cout << "Число " << n << " является простым" << endl;
    return true;
}

int main() {
    isPrime();
}