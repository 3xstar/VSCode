#include <iostream>
#include <vector>

struct Student{
    std::string name;
    double middle_grade;
    std::string lesson;
};

void best_student_in_biology(std::vector<Student> list)
{
    int most_grade;
    Student best_student;

    for(Student s : list){
        if(s.lesson == "biology"){
            if(s.middle_grade > most_grade){
                most_grade = s.middle_grade;
                best_student = s;
            }
        }
    }
    std::cout << "Студент с высшим баллом по биологии: " << best_student.name;
};

int main()
{
    std::vector<Student> students;
    Student s1 = {"Grisha", 4.3, "math"};
    Student s2 = {"Zahar", 2.9, "biology"};
    Student s3 = {"Slava", 3.2, "physics"};
    Student s4 = {"Borya", 4.7, "biology"};
    Student s5 = {"Vadim", 5, "english"};

    students.push_back(s1);
    students.push_back(s2);
    students.push_back(s3);
    students.push_back(s4);
    students.push_back(s5);

    best_student_in_biology(students);
}