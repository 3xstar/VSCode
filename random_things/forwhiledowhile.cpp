#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	setlocale(LC_ALL, "ru");

	/*
		for - счетчик
		while -  цикл с предусловием
		do while - цикл с постусловием
	*/

	int a = 7;

	for (int i = 0; i < 10; i++) {
		cout << "i = " << i << endl;
	}

	while (a < 10) {
		cout << a;
		a++;
	};
	
	do {
		cout << "Привет";
		a++;
	} while (a < 10);

	/*
		Задание 1.
		Проверка строки на палиндром;
	
		Задание 2.
		
	*/
	
}
