#include <iostream>
#include <random>
using std::cout;
using std::cin;
using std::endl;


int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> dist(0, 10);
    int random_number = dist(gen);

    int guess_number;

    cout << "Программа загадала случайное число в диапозоне от 0 до 10" << endl;
    cout << "Попробуй угадать рандомное число: ";
    cin >> guess_number;

    if(guess_number == random_number)
    {
        cout << "Ты угадал! :)" << endl;
    }
    else
    {
        cout << "Ты не угадал :(" << endl;
        while (guess_number != random_number)
        {    
            cout << "Попробуй еще раз угадать рандомное число: ";
            cin >> guess_number;

            if(guess_number == random_number)
            {
                cout << "Ты угадал! :)" << endl;
            }
            else
            {
            cout << "Ты не угадал :(" << endl;
            }
        }
    }
    
}