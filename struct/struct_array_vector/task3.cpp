#include <iostream>
#include <vector>

struct Student{
    std::string name;
    double middle_grade;
    std::string lesson;
};


void add_student(std::vector<Student>& students){
    std::string s_name;
    double s_grade;
    std::string s_lesson;

    std::cout << "Введите имя нового студента: ";
    std::cin >> s_name;

    std::cout << "Введите средний балл нового студента: ";
    std::cin >> s_grade;
 
    std::cout << "Введите название предмета: ";
    std::cin >> s_lesson;

    students.push_back({s_name, s_grade, s_lesson});
    std::cout << "Студент добавлен!" << std::endl;
}

void edit_student(std::vector<Student>& students){
    std::string s_name;
    int choice;

    std::cout << "Введите имя студента для редактирования: " ;
    std::cin >> s_name;

    for(int i = 0; i < students.size(); i++){
        if(students[i].name == s_name){
            std::cout << "1. Изменить имя\n2. Изменить балл\n3. Изменить предмет\nВыберите цифру нужного изменения: ";
            std::cin >> choice;

            switch(choice){
                case 1:
                {
                    std::string new_name;
                    std::cout << "Введите новое имя студента: ";
                    std::cin >> new_name;
                    students[i].name = new_name;
                    std::cout << "Имя студента изменено!" << std::endl;
                    break;
                }

                case 2:
                {
                    double new_grade;
                    std::cout << "Введите новый средний балл студента: ";
                    std::cin >> new_grade;
                    students[i].middle_grade = new_grade;
                    std::cout << "Средний балл студента изменен!" << std::endl;
                    break;
                }

                case 3:
                {
                    std::string new_lesson;
                    std::cout << "Введите новый предмет студента: ";
                    std::cin >> new_lesson;
                    students[i].lesson = new_lesson;
                    std::cout << "Предмет студента изменен!" << std::endl;
                    break;
                }
            };

            
        };
    }
}

void delete_student(std::vector<Student>& students){
    std::string s_name;
    
    std::cout << "Введите имя студента для удаления: " ;
    std::cin >> s_name;

    for(int i = 0; i < students.size(); i++){
        if(students[i].name == s_name){
            students.erase(students.begin() + i);
            std::cout << "Студент удален! " << std::endl;
        };
    }
}

void search_student(std::vector<Student>& students){
    std::string s_name;
    
    std::cout << "Введите имя студента для поиска: " ;
    std::cin >> s_name;

    for(int i = 0; i < students.size(); i++){
        if(students[i].name == s_name){
            std::cout << "Студент найден! " << std::endl;
            std::cout << "Имя студента: " << students[i].name <<std::endl;
            std::cout << "Средний балл студента: " << students[i].middle_grade <<std::endl;
            std::cout << "Предмет студента: " << students[i].lesson <<std::endl;
        };
    }
}

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

    add_student(students);
    edit_student(students);
    delete_student(students);
    search_student(students);
}