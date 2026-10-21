#include <iostream>

using namespace std;

class Array{
    private:
        int* data;
        int size;

    public:
        Array(int size) : size(size){
            data = new int[size]; // Выделяем память
            cout << "Память выделена" << endl;
        }
    
        ~Array() {
            delete[] data;
            cout << "Память освобождена" << endl;
        }
};

int main(){
    int *data;
    int size;
}