#include <iostream>
#include <vector>
using namespace std;

struct Student{
    string name;
    int age;
    double grade;
};

Student Borya{"Боря", 18, 3.69};
Student Zhora{"Жора", 17, 3.21};
Student Grisha{"Гриша", 19, 4.75};

vector<Student> students;

void bestStudent(const vector<Student>& vec){
    Student best = vec[0];

    for (const Student& s : vec){
        if(s.grade > best.grade){
            best = s;
        }
    }
    
    cout << "Студент с наивысшим баллом " << best.grade << ": " << best.name; 
}

void printStudent(Student& s){
    cout << "Имя студента: " << s.name << endl;
    cout << "Возраст студента: " << s.age << endl;
    cout << "Средний балл: " << s.grade << endl;
}

int main(){
    students.push_back(Borya);
    students.push_back(Grisha);
    students.push_back(Zhora);

    printStudent(Borya);
    printStudent(Grisha);
    printStudent(Zhora);

    bestStudent(students);
}