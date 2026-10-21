#include <iostream>
#include <fstream>

using namespace std;

class FileWrapper{
    private:
        ofstream log_file;

    public:
        FileWrapper(const string& filename){
            cout << "Opening file in constructor..." << endl;
            log_file.open(filename, ios::app);
            if(!log_file.is_open()){
                cout << "Error while trying to open file" << endl;
            }
            else{
                cout << "Success! File is opened" << endl;
            }
        }
    
    ~FileWrapper(){
        if(log_file.is_open()){
            log_file.close();
            cout << "File is closed in destructor" << endl;
        }
    }
};

int main(){
    FileWrapper f_w("task1.txt");
}