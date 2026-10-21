#include <iostream>

using namespace std;

class Engine{
    public:
        Engine(int p, string t){
            power = p;
            type = t;
            cout << "Двигатель создан" << endl;
        }

        ~Engine(){
            cout << "Двигатель уничтожен" << endl;
        }

        void start(){
            cout << "Двигатель запущен" << endl;
        }

        int get_power(){return power;}
        string get_type(){return type;}

    private:
        int power;
        string type;
};

class Car{
    public:
        Car(string b, int y, Engine eng):engine(eng){
            brand = b;
            year = y;
            cout << "Машина готова!" << endl;
        }

        ~Car(){
            cout << "Машина" << endl;
        }

        void drive(){
            cout << brand << "газует!";
        }

        string get_brand(){return brand;}

        int get_year(){return year;}

        Engine get_engine(){return engine;}
    
    private:
        string brand;
        int year;
        Engine engine;
};

int main(){
    Engine Grishanya(150, "Бензиновый"); // Создаем цельный объект
    Car lastochka("Toyota", 2020, Grishanya);
    cout << "Газ";
    lastochka.drive();

    // Композиция
    cout << "Мощность: " << Grishanya.get_power() << endl;
    cout << "Тип двигателя: " << Grishanya.get_type() << endl;
}