#include <iostream>

using namespace std;

// Структура
struct Student {
    string name;
    int age;
    double grade;
};

void showStudent(string name, int age, double grade) {
    cout << "Студент: " << name << "Возраст: " << age << "Ср. балл: " << grade;
};

void showStudent_Link(Student& s) {
    cout << "Студент: " << s.name << "Возраст: " << s.age << "Ср. балл: " << s.grade;
};

int main()
{
    setlocale(LC_ALL, "ru");

    // Способы объявления и инициализации структуры:
    // Способ 1.
    Student s1;
    s1.name = "Сергей";
    s1.age = 17;
    s1.grade = 3.8;

    // Способ 2
    Student s2 = {"Виталий", 23, 4.7}; // Старый способ

    // Способ 3
    Student s3{"Гришаня", 18, 2.8};

    showStudent(s1.name, s1.age, s1.grade);
    cout << "\n";
    showStudent_Link(s2);
}