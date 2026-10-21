#include <iostream>

using namespace std;

class Student{
    private:
        string name;
    
    public:
        Student(string n) : name(n){
            cout << name + " создан!" << endl;
        }

        ~Student(){
            cout << name + " уничтожен!" << endl;
        }
};

// Реализация
void function(){
    Student s1("Саша");
    Student s2("Катя");
} // Саша и Катя удаляются при завершении

int main(){
    function(); // Демонстрация работы
}