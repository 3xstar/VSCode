#include <iostream>

using namespace std;

struct Engine{
    string model;
    int power;
};

struct Car{
    string brand;
    int year;
    Engine engine;
};

void show_info(Car test_car){
    cout << "Бренд машины: " << test_car.brand << endl;
    cout << "Год выпуска: " << test_car.year << endl; 
    cout << "Название двигателя: " << test_car.engine.model << endl;
    cout << "Мощность двигателя: " << test_car.engine.power << endl; 
}

int main(){
    Engine for_car{"Twin-Turbo V8", 650};
    Car car{"Porsche", 2023, for_car};
    show_info(car);
}