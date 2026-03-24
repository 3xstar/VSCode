#include <iostream>

using namespace std;

class Car{
    public:
        void setBrand(const string& brand){
            if(!brand.empty()){
                this -> brand = brand;
            }
        }

        void setYear(int year){
            if(year >= 1900 && year <= 2026){
                this ->year = year;
            }
            else{
                cout << "Ошибка: неверный год (" << year << ")" << endl;
            }
        }

        void setSpeed(int speed){
            if(speed >= 0 && speed <= 300){
                this -> speed = speed;
            }
            else{
                cout << "Ошибка: неверная скорость (" << speed << ")" << endl;
            }
        }

        /// @brief Увеличение скорости
        /// @param delta
        void accelerate(int delta){
            int new_speed = this -> speed + delta;
            if(new_speed >= 0 && new_speed <= 300){
                this -> speed = new_speed;
                cout << "СкоростЬ: " << this -> speed << "км/ч" << endl;
            }
            else {
                cout << "Невозможно изменить скорость" << endl;
            }
        }

        /// @brief Замедление
        /// @param delta
        void brake(int delta){
            this -> accelerate(-delta);
        }

        string getBrand() const{
            return this -> brand;
        }

        int getYear() const{
            return this -> year;
        }

        int getSpeed() const{
            return this -> speed;
        }

        void displayInfo() const{
            cout << "Автомобиль:\nМарка: " << this -> brand << "\nГод: " << this-> year << "\nСкорость: " << this -> speed;
        }
        

    private:
        string brand;
        int year;
        int speed;
};

int main(){
    Car car;
    car.setBrand("Drandulet");
    car.setYear(1900);
    car.setSpeed(0);

    car.displayInfo();

    cout << "\nРазгон: " << endl;
    car.accelerate(100);
    car.accelerate(150);

    cout << "\nТорможение: " << endl;
    car.brake(50);

    cout << "\nПроверка валидации:" << endl;
    car.setYear(3000);
    car.setSpeed(-100);
    car.setSpeed(1000);
}