#include <iostream>
#include <stdexcept>
#include<fstream>

using namespace std;

void readFile(const string& name){
    try{
    ifstream file(name);
    if(!file.is_open()){
        throw runtime_error("Файл с данными не найден :(");
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
    cout << "Информация из файла с данными:" << endl;
    while(getline(file, info)){
            cout << info << endl;
    }
    file.close();

    }
    catch(const runtime_error& e){
        cout << "Ошибка: " << e.what();
    }
};

void copyFile(const string& name_from, const string& name_to){
    ifstream fin(name_from);
    ofstream fout(name_to);

    if(!fout.is_open()){
        throw runtime_error("Файл для копирования данных не найден :(");
    }
    cout << "Файл для копирования данных найден :)" << endl;

    char info;
    while(fin.get(info)){
        fout.put(info);
    }
    cout << "Данные успешно перенесены!";
}


int main(){
    try
    {
    throw runtime_error("Намеренная ошибка в main!");
    readFile("file.txt");
    cout << endl;
    copyFile("file.txt", "file2.txt");
    }
    
    catch(const exception& e){
        cout << "Произошла неизвестная ошибка";
    }
}