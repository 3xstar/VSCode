#include <iostream>
#include <string>
#include <algorithm>

using namespace std;


bool palindrom(string text){
    int left = 0;
    int right = text.length() - 1;

    while(left < right){
        if(tolower(text[left]) != tolower(text[right])) 
        {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

int main(){
    string words{"sas"};
    cout << "Текст: " << words << endl;
    cout << "Проверка палиндрома: " << palindrom(words);
} 