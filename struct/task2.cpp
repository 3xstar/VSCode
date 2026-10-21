#include <iostream>

using namespace std;

struct Track {
    string name;
    double duration;
    int numb_of_auditions;
};

Track lmb{"Let me bleed", 4.06, 1800000};

int main(){
    cout << "Название трека: " << lmb.name << endl;
    cout << "Длительность трека: " << lmb.duration << endl;
    cout << "Количество прослушиваний трека: " << lmb.numb_of_auditions << endl;
};