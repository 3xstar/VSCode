#include <iostream>

using namespace std;

class Student{
    public:
        Student(string name, double grade, int age){
            this -> name = name;
            this -> grade = grade;
            this -> age = age;
        }

        Student& setData(string name, double grade, int age){
            this -> name = name;

            if(1 <= grade <= 5){
                this -> grade = grade;
            }
            else{
                cout << "Недопустимый балл\n";
            }
            
            if(14 <= age <= 100){
                this -> age = age;
            }
            else{
                cout << "Студент не может быть моложе 14 или старше 100";
            }
        }

    private:
        string name;
        double grade;
        int age;
};