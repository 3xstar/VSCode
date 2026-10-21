#include <iostream>

int main(){
    //Сравнение строк
    std::string a = "Вторник";
    std::string b = "Среда";

    //Сравнение 1:
    if(a > b){
        std::cout << "В первом сравнении победил: " << a << std::endl;
    }
    else{
        std::cout << "В первом сравнении победила: " << b << std::endl;
    }


    //Сравнение 2:
    if(a < b){
        std::cout << "В первом сравнении победила: " << b << std::endl;
    }
    else{
        std::cout << "В первом сравнении победил: " << a << std::endl;
    }

    
    //Сравнение 3:
    if(a == b){
        std::cout << "a и b равны" << a << std::endl;
    }
    else{
        std::cout << "a и b не равны" << b << std::endl;
    }
}