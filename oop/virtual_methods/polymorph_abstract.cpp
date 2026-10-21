#include <iostream>

using namespace std;

// Базовый итнерфейс
class Logger{
    public:
        // Чисто виртуальная функция - нельзя инстанциировать
        virtual void log(const string& messsage) = 0;

        virtual ~Logger(){
            cout << "Логгер удален" << endl;
        }
};

// Консольный логгер
class ConsoleLogger : public Logger{
    public:
        void log(const string& message) override{
            cout << "Console - " << message << endl;
        }
};

// Файловый логгер
class FileLogger : public Logger{
    public:
        // final запрещает переопределение в наследниках FileLogger
        void log(const string& message) override final{
            cout << "File - " << message << endl;
        }
};

void process_logs(Logger* logger){
    logger -> log("Система запущена");
    logger -> log("Обработка данных");
    logger -> log("Завершение работы");
}

int main(){
    ConsoleLogger console;
    process_logs(&console);
    
    FileLogger file;
    process_logs(&file);

    cout << endl << "Logger - абстрактный класс. Его можно только наследовать";
}