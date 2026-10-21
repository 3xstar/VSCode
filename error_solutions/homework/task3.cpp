#include <iostream>
#include <stdexcept>
#include<fstream>

using namespace std;

void readFile(const string& name){
    try{
    ifstream file(name);
    if(!file.is_open()){
        throw runtime_error("Файл не найден :(");
    }
    cout << "Файл найден :)" << endl;

    char char_value;
    file.get(char_value);
    if(file.eof()){
        file.close();
        throw runtime_error("В файле нет какой-либо информации");
    }

    file.putback(char_value);
    string info;
    cout << "Информация из файла:" << endl;
    while(getline(file, info)){
            cout << info << endl;
    }
    file.close();

    }
    catch(const runtime_error& e){
        cout << "Ошибка: " << e.what();
    }
};



int main(){
    readFile("file.txt");
}