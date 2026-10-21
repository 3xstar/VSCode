#include <iostream>
using namespace std;

struct Student{
    string name;
    int age;
    double grade;
};

Student Borya{"Боря", 18, 3.69};

void increaseGrade(Student& s, double value){
    cout << "Имя студента: " << s.name << endl;
    cout << "Возраст студента: " << s.age << endl;
    cout << "Изначальный средний балл: " << value << endl;
    value++;
    cout << "Новый средний балл: " << value << endl;
}

int main(){
    increaseGrade(Borya, Borya.grade);
}