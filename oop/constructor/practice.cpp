#include <iostream>

using namespace std;


class Book{
    private:
        string title;
        int page_count;

    public:
        Book(){
            title = "Без имени";
            page_count = 0;
        }
};


class bookParams{
    private:
        string title;
        int page_count;

    public:
        bookParams(string t, int p){
            title = t;
            page_count = p;
        }
};

void printFunc(){
    Book b1;
    cout << "Создана книга без параметров!" << endl;
    bookParams b2("Белый клык", 100);
    cout << "Создана книга c параметрами!" << endl;
}

int main(){
    printFunc();
}