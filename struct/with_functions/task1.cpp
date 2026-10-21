#include <iostream>
using namespace std;

struct Book{
    string title;
    string author;
    int date_of_writing;
};

Book z{"Сигма", "Патрик Бейтман", 2007};

void printBook(const Book& s){
    cout << "Название книги: " << s.title << endl;
    cout << "Автор книги: " << s.author << endl;
    cout << "Год написания: " << s.date_of_writing << endl;
}

int main(){
    printBook(z);
}