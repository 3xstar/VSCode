#include <iostream>
#include <fstream>

using namespace std;

int main(){
    ifstream fin("from_copy.txt");
    ofstream fout("to_copy.txt");
    char info;

    while(fin.get(info)){
        fout.put(info);
    }

    cout << "Файл скопирован!";
}