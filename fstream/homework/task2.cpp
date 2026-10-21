#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(){
    ifstream fin("lines.txt");
    vector<string> lines;
    string line;
    int line_count = 0;

    cout << "Строки в lines.txt:" << endl;
    while(getline(fin, line)){
        cout << line << endl;
        line_count += 1;
        lines.push_back(line);
    }

    cout << "Количество строк: " << line_count;
}