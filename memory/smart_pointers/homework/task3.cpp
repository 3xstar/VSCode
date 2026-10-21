#include <iostream>
#include <memory>

using namespace std;

class Problem_Solution;

class Problem{
    public:
        shared_ptr<Problem_Solution> sp;
        // PROBLEM: shared ptr gonna stay in memory

    ~Problem(){
        cout << "Shared ptr eliminated" << endl;
    }
};

class Problem_Solution{
    public:
        weak_ptr<Problem> wp;
        // PROBLEM FIX: weak ptr removing shared ptr from memory

        void check_partner(){
            if(auto locked = wp.lock()){
                cout << "Weak ptr is alive" << endl;
            }
            else{
                cout << "Weak ptr is deleted" << endl;
            }
        }
    
    ~Problem_Solution(){
        cout << "Weak ptr eliminated" << endl;
    }
};


int main(){
    auto a = make_shared<Problem>();
    auto b = make_shared<Problem_Solution>();
    a->sp = b;
    b->wp = a;
    b->check_partner();

    cout << "Link counter value: " << a.use_count() << endl;
}