#include <iostream>
using namespace std;

void transform(int* a, int* b, int* c){
    int backup_a = *a;
    int backup_b = *b;
    *a *= 2;
    *b *= 3;
    *c = backup_a + backup_b + *c;
    cout << *a << endl;
    cout << *b << endl;
    cout << *c;
};

int main(){
    int* a = new int(3);
    int* b = new int(5);
    int* c = new int(10);
    cout << "Проведение операций:" << endl;
    transform(a, b, c);
    delete a;
    delete b;
    delete c;
};