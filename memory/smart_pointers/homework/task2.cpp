#include <iostream>
#include <memory>

using namespace std;

int main(){
    string object("Объект");
    auto data = make_shared<string>(object);

    shared_ptr<string> use1 = data;
    shared_ptr<string> use2 = data;

    cout << "Link counter value: " << data.use_count();
}