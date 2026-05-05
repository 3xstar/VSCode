#include <iostream>
#include <vector>

using namespace std;

class Ability {
public:
    virtual void use() = 0;
    virtual ~Ability() {}
};

class Fireball : public Ability{
public:
    void use() override{
        cout << "Нанесен урон огнем" << endl;
    }
};

class Heal: public Ability {
public:
    void use() override{
        cout << "Восстановлено здоровье" << endl;
    }
};

class Shield: public Ability{
public:
    void use() override{
        cout << "Активирован щит" << endl;
    }
};

class Clone : public Ability{
public:
    void use() override{
        cout << "Создан клон" << endl;
    }
};

class Invisibility : public Ability {
public:
    void use() override{
        cout << "Применена невидимость" << endl;
    }
};


int main(){
    vector<Ability*> abilities;

    abilities.push_back(new Fireball());
    abilities.push_back(new Heal());
    abilities.push_back(new Shield());
    abilities.push_back(new Clone());
    abilities.push_back(new Invisibility());

    for(Ability* ab : abilities){
        ab->use();
    }

    for(Ability* ab : abilities){
        delete ab;
    }
}