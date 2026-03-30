#include <iostream>

using namespace std;

class Counter{
    public:
        Counter(int v) : value(v){}

        // Оператор инкремента(префиксный)
        Counter& operator++(){
            value++; // Увеличиваем value на 1
            return *this;
        }

        // Оператор инкремента(постфиксный)
        Counter& operator++(int){
            Counter temp = *this;
            value++;
            return temp;
        }

    private:
        int value;
};

int main(){
    Counter counter(10);
    ++counter;
    counter++;
}