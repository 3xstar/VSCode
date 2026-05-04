#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class HeavyResources{
    public:
        HeavyResources() {cout << "HeavyRecources создан" << endl;}
        ~HeavyResources() {cout << "HeavyRecources удален" << endl;}
        void process() {cout << "Обработка ресурса" << endl;}
};

void test_raw_pointer(){
    HeavyResources* res = new HeavyResources();
    res->process();
    if(true){
        cout << "Тут поймаем утечку";
        return;
    }

    delete res; // Данная строка не выполниться
}

void test_unique_ptr(){
    auto res = make_unique<HeavyResources>(); // Захват в коснтрукторе
    res->process();
    if(true){
        cout << "Деструктор вызывается автоматически, утечка не будет" << endl;
        return;
    }
}

void test_exception_safety(){
    try{
        auto res = make_unique<HeavyResources>();
        res->process();
        throw runtime_error("Ошибка!");
    } catch(const exception& e){
        cout << "Исключение:" << e.what() << endl;
        cout << "Ресурс уже освобожден" << endl;
    }
}

int main(){
    test_raw_pointer();
    test_unique_ptr();
    test_exception_safety();
}