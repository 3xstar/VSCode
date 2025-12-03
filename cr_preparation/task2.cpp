#include <iostream>
using namespace std;

int reversenumber(int numb, int reversed = 0)
{
    if (numb == 0) {
        return reversed;
    }

    int lastdigit = numb % 10; 
    int remainingnumb = numb / 10;
    int newreversed = reversed * 10 + lastdigit;

    return reversenumber(remainingnumb, newreversed);
}

int main() 
{
    int user_numb;
    cout << "Введите число для переворота: ";
    cin >> user_numb;

    cout << "Перевернутое число: " << reversenumber(user_numb);
}