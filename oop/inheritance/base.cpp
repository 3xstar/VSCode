#include <iostream>
using namespace std;

class Animal{
    protected:
        string name; // Кличка
        int age; // Возраст
        string species; // Особенности

    public:
        Animal(string n, int a, string sp){
            name = n;
            age = a;
            species = sp;
            cout << "Мы создали питомца" << endl;
        }
        ~Animal(){
            cout << "Питомца забрали" << endl;
        }

        void eat(){
            cout << name << " кушает" << endl;
        }

        void sleep(){
            cout << name << " спит" << endl;
        }

        void make_sound(){
            cout << name << " издает звук" << endl;
        }

        string get_name(){return name;}
        int get_age(){return age;}
        string get_species(){return species;}
};

class Dog : public Animal{
    public:
        Dog(string n, int a, string sp, string br, bool trained) : Animal(n, a, sp){
            breed = br;
            is_trained = trained;
            cout << "Создан мощный пес" << endl;
        }

        ~Dog(){
            cout << "Мощный пес ушел гулять" << endl;
        }

        void run_to_stick(){
            cout << "Пес пошел за палкой" << endl;
            if(is_trained){
                cout << "Пес принес палку" << endl;
            }

            else{
                cout << "Пес написал на соседский куст" << endl;
            }
        }
        
        void make_sound(){
            cout << name << " пес гавнул" << endl;
            if(is_trained){
                cout << "Пес съел соседа" << endl;
            }

            else{
                cout << "Пес съел тебя" << endl;
            }
        }

        void show_info(){
            cout << "Собака: " << name << "\nвозраст: " << age << "\nпорода: " << breed << "\nСтатус: " << (is_trained? "Дрессирован" : "Не дрессирован");
        }

        private:
            string breed; // Порода
            bool is_trained; // Статус дрессировки
};

class Cat : public Animal{

    public:
        Cat(string n, int a, string sp, string c, bool cast) : Animal(n, a, sp){
            color = c;
            is_castrated = cast;
            cout << "Взяли кошку" << endl;
        }

        ~Cat(){
            cout << "Кошка ушла в лес" << endl;
        }

        void meow(){
            cout << "Кошка мяукнула" << endl;
        }
        
        void purr(){
            cout << "Кошка мурчит" << endl;
        }

        void make_sound(){
            cout << name << " мяукает" << endl;
        }

        void show_info(){
            cout << "Кошка: " << name << "\nвозраст: " << age << "\nцвет: " << color << "\nКастрация: " << (is_castrated? "Не анлак" : "Анлак");
        }        

    private:
        string color;
        bool is_castrated;
};

int main(){
    Dog dog{"Виталя", 3, "Пес", "Лабрадор", true};
    Cat cat{"Мишаня", 2, "Кот", "Рыжий", true};

    cout << "Животные дают бассов:" << endl;
    dog.make_sound();
    cat.make_sound();

    cout << "Наследованный контент:" << endl;
    dog.eat();
    cat.sleep();

    cout << "Палка:" << endl;
    dog.run_to_stick();

    cout << "Кошачьи мувы:" << endl;
    cat.meow();
    cat.purr();
}