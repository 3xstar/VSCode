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
    string words{"This is english text"};
    cout << "Строка: " << words << endl;
     
    string max_word = " ";
    for(auto w : split(words, ' ')){
        if(w.size() > max_word.size()){
            max_word = w;
        }
    }

    cout << "Наибольшее слово: " << max_word << endl;
}