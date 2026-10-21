#include <iostream>

using namespace std;

// Список инициаплизации - последовательность вызова свойств

class Student{
    public:
        // Использование списка инициализации является самым правильным подходом
        Student(string n, int a) : name(n), age(a){
            cout << "Студент создан!" << endl;
        }
        // Большой плюс заключается в том, что список работает быстрее присваивания

    private:
        string name;
        int age;
};

int main(){
    Student("Артем", 16);
}