#include <iostream>
#include <cctype>

using namespace std;

int main() 
{
    int wordcount = 0;
    int consonantlettercount = 0;
    int symbolcount = 0;
    string text;
    bool inword = false;
    string consonants = "bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ";

    cout << "Введите набор слов с символами (на английском языке): ";
    getline(cin, text);

    for (char c : text) {
        if (isspace(c) || ispunct(c) || iscntrl(c))
        {
            symbolcount++;
        }

        if (isalpha(c) && consonants.find(c) != std::string::npos)
        {
            consonantlettercount++;
        }

        if (isspace(c))
        {
            inword = false;
        }
        else if (!inword)
        {
            wordcount++;
            inword = true;
        }
    }

    cout << "Количество слов: " << wordcount << endl;
    cout << "Количество согласных букв: " << consonantlettercount << endl;
    cout << "Количество символов: " << symbolcount << endl;

    return 0;
}