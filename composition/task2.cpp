#include <iostream>
#include <vector>

using namespace std;

struct Author{
    string name;
    string country;
};

struct Book{
    string title;
    int year;
    Author author;
};

void show_info(Book test_book){
    cout << "Название книги: " << test_book.title << endl;
    cout << "Год выпуска книги: " << test_book.year << endl; 
    cout << "Имя автора: " << test_book.author.name << endl;
    cout << "Страна: " << test_book.author.country << endl; 
}

int main(){
    Author dostoevsky{"Федор Достоевский", "Россия"};
    Book crime_and_punishment{"Преступление и наказание", 1866, dostoevsky};

    Author hemingway{"Эрнест Хемингуэй", "США"};
    Book the_old_man_and_the_sea{"Старик и море", 1952, hemingway};

    vector<Book> library{crime_and_punishment, the_old_man_and_the_sea};
    for(Book& b : library){
        show_info(b);
        cout << endl;
    }
}