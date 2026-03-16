#include <iostream>

using namespace std;

class DynamicBuffer{
    private:
        int* data;
        int size;

    public:
        DynamicBuffer(int size) : size(size){
            data = new int[size]; // Выделяем память
            cout << "Память выделена" << endl;
        }

        void filling(){
            cout << "Заполнение динамического массива:" << endl;
            for(int i = 0; i < size; i++){
                data[i] = i;
                cout << "Добавлен элемент: " << data[i] << endl;
            }
            cout << "Заполнение закончено" << endl;
        }
    
        ~DynamicBuffer() {
            delete[] data;
            cout << "Память освобождена" << endl;
        }
};

int main(){
    DynamicBuffer dynamic_buffer(10);
    dynamic_buffer.filling();
}