#include <iostream>
#include <vector>

using namespace std;

vector<string> split(const string&s, char delim){
	vector<string> res;
	string cur;

	for(char c : s){
		if (c == delim){
			res.push_back(cur);
			cur.clear();
		} else{
			cur += c;
		}
	}
	res.push_back(cur);
	return res;
}

int main(){
    string words{"x=10;y=20;z=30"};
    cout << "Строка: " << words << endl;
    

    int sum = 0;
    for(auto w : split(words, ';')){
        string number = w.substr(2,4);
        sum += stoi(number);
    }

    cout << "Сумма элементов: " << sum;
}