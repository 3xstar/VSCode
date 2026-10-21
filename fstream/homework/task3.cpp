#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(){
    ifstream fin("lines.txt");
    vector<string> lines;
    string line;
    string biggest_line = "";

    cout << "Строки в lines.txt:" << endl;
    while(getline(fin, line)){
        cout << line << endl;
        if(line.size() > biggest_line.size()){
            biggest_line = line;
        }
        lines.push_back(line);
    }

    cout << "Наибольшая строка: " << biggest_line;
}