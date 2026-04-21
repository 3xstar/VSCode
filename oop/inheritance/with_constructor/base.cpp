#include <iostream>

using namespace std;

class Vehicle{
    protected:
        string brand;

    public:
        Vehicle(string b){
            brand = b;
            cout << "Транспортное средство создано" << endl;
        }

        // Виртуальный метод
        virtual void info(){
            cout << "Бренд: " << brand << endl;
        }
};

class Car : public Vehicle{
    private:
        string model;

    public:
        Car(string b, string m) : Vehicle(b){
            model = m;
            cout << "Машина создана";
        }

        // Переопределение метода
        void info() override {
            cout << "\nМашина бренда: " << brand << "\nмодели: " << model << endl;
        }
};

int main(){
    Car car("New", "TBS-123");

    car.info(); // Вывод информации, используя переопределяющий метод
}
