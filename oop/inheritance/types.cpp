#include <iostream>

using namespace std;

// Родительский класс
class Base{
    public:
        int public_var;
    
    protected:
        int protected_var;

    private:
        int private_var;

    public:
        Base(int pub, int prot, int priv){
            public_var = pub;
            protected_var = prot;
            private_var = priv;
            cout << "public: " << public_var << "\nprotected: " << protected_var << "\nprivate: " << private_var << endl;
        }

        ~Base(){
            cout << "Base пал" << endl;
        }

        void show_base(){

        }
};

// Public наследование: все останется как есть
class DerivedPublic : public Base{
    public:
        DerivedPublic(int pub, int prot, int priv) : Base(pub, prot, priv){
            cout << "Класс Public создан" << endl;
        }
    
        void show_derived(){
            // public_var - доступен(public)
            // protected_var - доступен(proteted)
            // private_var - недоступен(private)
            cout << "public: " << public_var << "\nprotected: " << protected_var;
        }
};

// Protected наследование: public становится protected
class DerivedProtected : protected Base{
    public:
        DerivedProtected(int pub, int prot, int priv) : Base(pub, prot, priv){
            cout << "Класс protected создан" << endl;
        }

    void show_derived(){
        // public_var - стал protected
        // protected_var - остался protected
        // private_var - недоступен
        cout << "public: " << public_var << "\nprotected: " << protected_var;
    }
};

// Private наследование: все становится private
class DerivedPrivate: private Base{
    public:
        DerivedPrivate(int pub, int prot, int priv) : Base(pub, prot, priv){
            cout << "Класс private создан" << endl;
        }

    void show_derived(){
        // public_var - стал private
        // protected_var - стал private
        // private_var - недоступен 
    }
};


int main(){
    DerivedPublic pub_obj(1, 2, 3);
    pub_obj.show_base();
    pub_obj.show_derived();

    DerivedProtected prot_obj(1, 2, 3);
    prot_obj.show_derived();
    // prot_obj.show_base() Будет ошибка, так как show_base() теперь protected

    DerivedPrivate priv_obj(1, 2, 3);
    priv_obj.show_derived();
    // priv_obj.show_base() Будет ошибка, так как show_base() теперь private

}