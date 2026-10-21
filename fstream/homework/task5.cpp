#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(){
    ifstream fin("space_is_char.txt");
    vector<string> file;
    string line;

    cout << "Строки в lines.txt:" << endl;
    while(getline(fin, line)){
        for(char& c : line){
            if(c == ' '){
                c = '_';
            }
        }
        file.push_back(line);
        cout << line << endl;
    }
}