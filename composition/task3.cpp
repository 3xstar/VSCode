#include <iostream>
#include <vector>

using namespace std;

struct Student{
    string name;
    string town;
};

void students_in_town(vector<Student> test_list){
    string search_town;
    cout << "Введите название города для поиска студентов: ";
    cin >> search_town;

    cout << "Студенты в городе " << search_town << ":" << endl;
    for(Student s : test_list){
        if(search_town == s.town){
            cout << s.name << endl;
        }
    }
}

int main(){
    Student Borya{"Боря", "Москва"};
    Student Andrey{"Андрей", "Иркутск"};
    Student Vova{"Вова", "Ангарск"};
    Student Nikita{"Никита", "Иркутск"};
    vector<Student> student_list{Borya, Andrey, Vova, Nikita};

    students_in_town(student_list);
}

//Почему композиция безопаснее наследования на ранних этапах разработки?

//Композиция даёт больше гибкости 
//и меньше связывает классы между собой, 
//что упрощает изменения на ранних этапах.