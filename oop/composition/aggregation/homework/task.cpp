#include <iostream>

using namespace std;

class Teacher{
    public:
        string name;
    public:
        Teacher(string name){
            this->name = name;
        }
};

class Course{
    private:
        Teacher* teacher;
    
    public:
        Course(Teacher* teacher){
            this->teacher = teacher;
        }

        void show_teacher(){
            cout << "Имя преподавателя: " << teacher->name << endl;
        }
};

int main(){
    Teacher teacher("Ольга");
    
    Course course(&teacher);
    course.show_teacher();
}