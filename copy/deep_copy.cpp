// ===================Глубокое копирование===================

#include <iostream>

using namespace std;

class Array{
    public:
        Array(int size) : size(size){
            data = new int[size];
            cout << "Память выделена" << endl;
        }

        // Гуд: копирование
        Array(const Array& other) : size(other.size){
            data = new int[size];
            for (int i=0; i<size; i++){
                data[i] = other.data[i];
            }
            cout << "Выполнено глубокое копирование" << endl;
        }

        ~Array(){
            delete[] data;
            cout << "Память освобождена" << endl;
        }

private:
        int* data;
        int size;
};

int main(){

}