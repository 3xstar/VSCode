#include <iostream>

using namespace std;

class Employee{
    private:
        string name;
    
    public:
        Employee(string n){
            name = n;
        }

        ~Employee(){
            cout << "The employee has done his job" << endl;
        }

        void work(){
            cout << "The employee " << name << " started working" << endl;
        }
};

class Manager : Employee{
    private:
        string name;

    public:
        Manager(string n) : Employee(n){
            name = n;
        }

        ~Manager(){
            cout << "The manager has done his job" << endl;
        }

        void work(){
            cout << "The manager " << name << " started working" << endl;
        }
        
        void manage(){
            cout << name << " is managing..." << endl;
        }
};

class Developer : Employee{
    private:
        string name;

    public:
        Developer(string n) : Employee(n){
            name = n;
        }

        ~Developer(){
            cout << "The developer has done his job" << endl;
        }

        void work(){
            cout << "The developer " << name << " started working" << endl;
        }

        void coding(){
            cout << name << " is coding..." << endl;
        }
};

int main(){
    Employee Grisha("Гриша");
    Manager Borya("Боря");
    Developer Sanya("Саня");

    Grisha.work();
    cout << endl;

    Borya.work();
    Borya.manage();
    cout << endl;

    Sanya.work();
    Sanya.coding();

    cout << "\n";
}

