#include <iostream>
#include <stdexcept>
#include<fstream>

using namespace std;

int readFile(const string& name){
    ifstream file(name);
    if(!file.is_open()){
        cout << "Файл не найден :(";
        return 0;
    }
    cout << "Файл найден :)" << endl;

    char char_value;
    file.get(char_value);
    if(file.eof()){
        cout << "В файле нет какой-либо информации" << endl;
        file.close();
        return 0;
    }

    else{
        file.putback(char_value);
        string info;
        cout << "Информация из файла:" << endl;
        while(getline(file, info)){
            cout << info << endl;
        }
    file.close();
    return 0;
    }
};



int main(){
    readFile("file.txt");
}