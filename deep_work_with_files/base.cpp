#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <stdexcept>
using namespace std;

#pragma pack(push, 1)
struct Student
{
    char name[30];
    int age;
    double gpa;
};
#pragma pack(pop)

void save_students_binary(const string& filename, const vector<Student>& students){
    ofstream file(filename, ios::binary | ios::trunc);
    if(!file.is_open()) throw runtime_error("Не удалось открыть файл " + filename + " и записать в него информацию");
    size_t count = students.size();
    file.write(reinterpret_cast<const char*>(&count), sizeof(size_t));
    for (const auto& s : students){
        file.write(reinterpret_cast<const char*>(&s), sizeof(Student));
    }
    if (file.fail()) throw runtime_error("Ошибка записи данных");
    file.close();
}

vector<Student> load_students_binary(const string& filename){
    ifstream file(filename, ios::binary);
    if(!file.is_open()) throw runtime_error("Файл не найден");
    vector<Student> students;
    size_t count = 0;
    file.read(reinterpret_cast<char*>(&count), sizeof(size_t));
    if(file.fail()) throw runtime_error("Ошибка чтения заголовка или пустой файл");
    students.reserve(count);
    for(size_t i = 0; i < count; ++i){
        Student s;
        file.read(reinterpret_cast<char*>(&s), sizeof(Student));
        students.push_back(s);
    }
    if(file.fail() && !file.eof()) throw runtime_error("Файл поврежден");
    file.close();
    return students;
}

int main(){
    setlocale(LC_ALL, "ru");
    try{
        // Запись в файл
        vector<Student> original = {
            {"Zahar", 18, 4.9},
            {"Nikita", 17, 4.7},
            {"Vova", 17, 4.5},
        };

        save_students_binary("students.dat", original);
        cout << "Успешно сохранено " << original.size() << " запись" << endl;

        // Выгрузка из файла
        vector<Student> loaded = load_students_binary("students.dat");
        cout << "Успешно загружено" << endl;

        // Восстановление данных
        for(const auto& s : loaded){
            cout << "Имя: " << s.name << " | Возраст: " << s.age << " | СБ: " << fixed << setprecision(1) << s.gpa << endl;
        }
    }
    catch(const exception& e){
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }
}