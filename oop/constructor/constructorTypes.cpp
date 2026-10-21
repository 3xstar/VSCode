#include <iostream>

using namespace std;

// Создание конструктора
// По умолчанию конструктор создается без параметров

class Phone{
    private:
        string brand;
        int price;

    public:
        //Конструктор
        Phone(){
            brand = "Noname";
            price = 0;
        }
};

// Виды конструкторов

// 1. Конструктор по умолчанию
class Student{
    private:
        string name;
        int age;

    public:
        //Конструктор
        Student(){
            name = "Без имени";
            age = 0;
            cout << "Создан студент по умолчанию!" << endl;
        }
};

// 2. Конструктор с параметрами
class StudentParams{
    private:
        string name;
        int age;

    public:
        StudentParams(string n, int a){
            name = n;
            age = a;
            cout << "Создан студент: " << name << " возраст: " << age << endl;
        }
};

// 3. Конструктор с параметрами по умолчанию
class StudentParamsDefault{
    private:
        string name;
        int age;

    public:
        StudentParamsDefault(string n = "Неизвестно", int a = 0){
            name = n;
            age = a;
            cout << "Создан студент: " << name << " возраст: " << age << endl; 
        }
};

int main(){
    Student s1;
    StudentParams s2("Илья", 18);
    StudentParamsDefault s3;
}