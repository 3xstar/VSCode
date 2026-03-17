#include <iostream>

using namespace std;

class Person{
    private:
        int age;

    public:
        void setAge(int age){
            if (age > 0 && age < 120){
                this-> age = age;
            }
        }

        int getAge(){
            return this->age;
        }
};

int main(){
    Person Bob;
    Bob.setAge(15);
    cout << "Бобу сегодня исполнилось: " << Bob.getAge() << " лет" << endl;
}