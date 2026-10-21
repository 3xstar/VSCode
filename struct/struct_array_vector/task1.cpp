#include <iostream>
#include <array>

struct Student{
    std::string name;
    double middle_grade;  
};

Student group[4]{{"Саша", 2.7},{"Захар", 4.7},{"Вадим", 3.4},{"Боря", 4.9}};

int main()
{
std::cout << "Студенты с баллом выше 4.5: " << std::endl;
for (const auto& student : group){
    if(student.middle_grade > 4.5){
        std::cout << "Имя: " << student.name << " | Балл: " << student.middle_grade << std::endl;}
    }
}