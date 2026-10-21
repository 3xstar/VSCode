#include <iostream>
#include <string_view>

using namespace std;


int word_count(string_view text){
    int words = 0;
    bool is_word = false;
    for (char word : text){
        if(isspace(word)) {
            is_word = false; 
        }
        else if(!is_word){
            words++;
            is_word = true;
        }
    }
    return words;
}

int main(){
    string_view words{"This is english text"};
    cout << "Текст: " << words << endl;
    cout << "Количество слов: " << word_count(words);
}