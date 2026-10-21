#include <iostream>
#include <fstream>

using namespace std;

class DynamicArray{
    private:
        int* arr;

    public:
        DynamicArray(int size){
            cout << "Memory allocation in constructor..." << endl;
            arr = new int[size];
        }
    
    ~DynamicArray(){
        cout << "Freeing up memory in destructor..." << endl;
        delete[] arr;
        cout << "Success!";
    }
};

int main(){
    DynamicArray d_a(10);
}