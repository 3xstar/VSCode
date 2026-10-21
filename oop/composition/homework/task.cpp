#include <iostream>

using namespace std;

class Processor{
    private:
        string name;
        int core_amount;
        double clock_speed;

    public:
        Processor(string n, int c_a, double c_s){
            name = n;
            core_amount = c_a;
            clock_speed = c_s;
        }

        void start(){
            cout << "Процессор " << name << " запущен" << endl;
        }
};

class RAM{
    private:
        string name;
        string type;
        int gb_amount;
        int numb_of_slots;

    public:
        RAM(string n, string t, int g_a, int n_of_s){
            name = n;
            type = t;
            gb_amount = g_a;
            numb_of_slots = n_of_s;
        }

        void start(){
            cout << "ОЗУ " << name << " в размере " << numb_of_slots << " плашек запущена" << endl;
        }
};

class GPU{
    private:
        string name;
        string company;
        int gb_amount;

    public:
        GPU(string n, string c, int g_a){
            name = n;
            company = c;
            gb_amount = g_a;
        }

        void start(){
            cout << "Видеокарта " << name << " запущена" << endl;
        }
};

class Computer{
    public:
        Computer(Processor p, RAM r, GPU g) : processor(p), ram(r), gpu(g){
            cout << "Компьютер собран!\n" << endl;
        }

        void start(){
            cout << "Запуск компьютера..." << endl;
            processor.start();
            ram.start();
            gpu.start();
            cout << "\nКомпьютер готов к работе!" << endl;
        }

        ~Computer(){
            cout << "Компьтер взорвался, анлак анлак :(";
        }

    private:
        Processor processor;
        RAM ram;
        GPU gpu;
};

int main(){
    Processor p("Intel Core I9", 12, 3.4);
    RAM ram("HyperX", "DDR5", 8, 4);
    GPU gpu("NVDIA 5090 TI", "GIGABYTE", 20);

    Computer best_computer(p, ram, gpu);
    best_computer.start();
}

