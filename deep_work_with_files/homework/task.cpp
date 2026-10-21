#include<iostream>
#include<fstream>

using namespace std;

int main(){
    ifstream fin("data.txt");
    string line;

    int lines_counter = 0;
    int symbols_counter = 0;
     
    while(getline(fin, line)){
        lines_counter ++;
        for(int i=0; i < line.size(); i++){
            symbols_counter ++;
        }
    }
    
    cout << "Lines counter: " << lines_counter << endl;
    cout << "Symbols counter: " << symbols_counter << endl;

    ofstream fout("result.txt");
    fout << "LINES COUNT: " << lines_counter << endl;
    fout << "SYMBOLS COUNT: " << symbols_counter << endl;

    fin.close();
    fout.close();
}
