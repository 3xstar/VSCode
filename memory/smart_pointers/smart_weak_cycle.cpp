#include <iostream>
#include <memory>

using namespace std;

struct NodeB;

struct NodeA{
    shared_ptr<NodeB> partner;
    ~NodeA(){
        cout << "NodeA удалена" << endl;
    }
};

struct NodeB{
    weak_ptr<NodeA> partner;
    ~NodeB(){
        cout << "NodeB удалена" << endl;
    }

    void check_partner(){
        if(auto locked = partner.lock()){
            cout << "NodeA существует" << endl;
        }
        else{
            cout << "NodeA удалена" << endl;
        }
    }
};

int main(){
    auto a = make_shared<NodeA>();
    auto b = make_shared<NodeB>();
    a->partner = b;
    b->partner = a; // weak_ptr
    cout << "Количество ссылок: " << a.use_count() << endl;
}