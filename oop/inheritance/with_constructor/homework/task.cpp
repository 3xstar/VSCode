#include <iostream>
using namespace std;

class Character
{
    protected:
        string name;

    public:
        Character(string Name){
            name = Name;
        }

        virtual void attack(){
            cout << "Персонаж " << name << " атакует!" << endl;
        }
        
        virtual ~Character(){
            cout << "Персонаж " << name << " покинул игру" << endl;
        }
};

class Warrior : public Character{
    private:
        int damage;
        string weapon;
    
    public:
        Warrior(string Name, int d, string w) : Character(Name){
            damage = d;
            weapon = w;
        }

        void attack() override{
            cout << "Воин " << name << " наносит " << damage << " урона используя " << weapon << endl;
        }

        void Slash(){
            cout << "Воин " << name << " использует прием Slash нанося " << damage + 5 << " урона" << endl;
        }
};

class Mage : public Character{
    private:
        int damage;
        string basic_spell;
        string special_spell;
    
    public:
        Mage(string Name, int d, string basic_s, string special_s) : Character(Name){
            damage = d;
            basic_spell = basic_s;
            special_spell = special_s;

        }

        void attack() override{
            cout << "Маг " << name << " использует базовое заклинание " << basic_spell << " нанося " << damage << " урона" << endl;
        }

        void castSpell(){
            cout << "Маг " << name << " кастует специальное заклинание " << special_spell << " нанося " << damage + 10 << " урона" << endl;
        }
};

int main(){
    Warrior Borya("Боря", 30, "Flame Sword");
    Borya.attack();
    Borya.Slash();

    Mage Sasha("Саша", 25, "Flame Sphere", "Meteor Waves");
    Sasha.attack();
    Sasha.castSpell();
}