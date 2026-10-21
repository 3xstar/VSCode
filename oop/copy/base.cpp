#include <iostream>

using namespace std;

class Student{
public:
        Student(string n, int a) : name(n), age(a){}

        Student(const Student& other){
            name = other.name;
            age = other.age;
        }

        void show_info(){
            cout << "Имя студента: " << name;
        };

private:
        string name;
        int age;
};

// Проблема поверхностного копирования
class Array{
    public:
        Array(int size) : size(size){
            data = new int[size];
        }

        // Плохо: поверхностное копирование
        Array(const Array& other){
            data = other.data;
            size = other.size;
        }
        
    private:
        int* data;
        int size;
};

int main(){
    Student s1("Алексей", 15);
    Student s2 = s1; // Копирование объекта
    Student s3(s1); // Копирование другим способом

    s1.show_info();
    s2.show_info();
    s3.show_info();

    // Проблема:
    Array a1(5);
    Array a2 = a1; // Оба объекта указывают на одну и ту же память

    /*
    Когда а1 и а2 уничтожается, delete[] вызовется дважды для одной памяти
    Ошибка: двойное высвобождение памяти
    */
}