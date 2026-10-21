#include <iostream>

using namespace std;

class Device
{
    protected:
        string name;
        bool is_on = false;
    
    public:
        Device(string Name){
            name = Name;
        }

        void turnOn(){
            is_on = true;
        }

        void turnOff(){
            is_on = false;
        }

        ~Device(){};
};

class Light : public Device{
    private:
        int brightness_power;

    public:
        Light(string Name, double Brightness_power) : Device(Name){
            brightness_power = Brightness_power;
        }

        void LightOn(){
            turnOn();
            cout << "Светильник " << name << " включен" << endl;
        }

        void LightOff(){
            turnOff();
            cout << "Светильник " << name << " выключен" << endl;
        }

        void ShowBrightness(){
            cout << "Мощность яркости светильника: " << brightness_power << endl;
        }

        ~Light(){cout << "Светильник отрубился" << endl;}
};

class Thermostat : private Device{
    private:
        double temperature;

    public:
        Thermostat(string Name, double Temperature) : Device(Name){
            temperature = Temperature;
        }

        void TermoOn(){
            turnOn();
            cout << "Терморегулятор " << name << " включен" << endl;
        }

        void TermoOff(){
            turnOff();
            cout << "Терморегулятор " << name << " выключен" << endl;
        }

        void ShowTemperature(){
            cout << "Терморегулятор показывает температуру: " << temperature << endl;
        }

        ~Thermostat(){cout << "Терморегулятор отрубился" << endl;}
};

int main(){
    Light light("White Cat", 700);
    Thermostat thermostat("Temperature Master", 30);

    light.LightOn();
    light.LightOff();
    light.ShowBrightness();

    thermostat.TermoOn();
    thermostat.TermoOff();
    thermostat.ShowTemperature();
}