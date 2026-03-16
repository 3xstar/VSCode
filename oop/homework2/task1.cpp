#include <iostream>

using namespace std;

class Book{
    private:
        string name;
        int pages_count;

    public:
        Book(string n, int p_c){
            name = n;
            pages_count = p_c;
        }

        void setData(){
            cout << "Enter the new name of book: ";
            cin >> name;

            cout << "Enter the new pages count of book: ";
            cin >> pages_count;

            cout << "Params of book changed!" << endl;
        }

        void setData(string newName, int newPagesCount){
            name = newName;
            pages_count = newPagesCount;
            cout << "Params of book changed!" << endl;
        };

        void printInfo(){
            cout << "Name of the book: " << name << endl;
            cout << "Pages count of the book: " << pages_count << endl;
        }
};

int main(){
    Book b1("Белый клык", 150);
    b1.printInfo();
    cout << endl;
    b1.setData("Война и мир", 999999);
    cout << endl;
    b1.printInfo();
}