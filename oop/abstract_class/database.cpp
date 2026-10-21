#include <iostream>
#include <vector>
#include <memory>

using namespace std;

// Интерфейс БД
class IDatabase {
    public:
        virtual ~IDatabase() = default;
        virtual bool connect(const string& host) = 0;
        virtual string query(const string& sql) = 0;
        virtual void disconnect() = 0;
        virtual string get_driver_name() const = 0;
};

// Реализация MySQL
class MySQLDriver : public IDatabase{
    private:
        bool connected = false;
        string current_host;
    
    public:
        bool connect (const string& host) override {
            cout << "[MySQL] подключен к " << host << endl;
            current_host = host;
            connected = true;
            return true;
        }

        string query(const string& sql) override{
            if(!connected) return "Ошибка! Отсутствует подключение";
            cout << "[MySQL] выполняем: " << sql << endl;
            return "Запрос выполнен успешно";
        }

        void disconnect() override{
            cout << "[MySQL] отключение от " << current_host << endl;
            connected = false;
        }

        string get_driver_name() const override {return "MySQL 8.0";}
};


// Реализация PostgreSQL
class PostgresDriver : public IDatabase{
    private:
        bool connected = false;
    
    public:
        bool connect(const string& host) override{
            cout << "[PG] подключение к " << host << endl;
            connected = true;
            return true;
        }

        string query(const string& sql) override{
            if(!connected) return "Ошибка! Отсутствует подключение";
            cout << "[PG] выполняем: " << sql << endl;
            return "Запрос выполнен успешно";
        }

        void disconnect() override{
            cout << "[PG] отключение" << endl;
            connected = false;
        }

        string get_driver_name() const override {return "PostgreSQL 14";}
};

// Симуляция бизнес-логики, работающая с абстрактией
class UserRepository{
    private:
        IDatabase& db; // Ссылка на интерфейс

    public:
        // expilcit - модификатор запрещающий неявные преобразования в коснструкторе
        explicit UserRepository(IDatabase& database) : db(database){}

        void load_users(){
            string result = db.query("SELECT * from users");
            cout << "Ответ БД: " << result << endl;
        }
};

int main(){
    MySQLDriver mysql;
    mysql.connect("localhost:3306");

    UserRepository repo_mysql(mysql);
    repo_mysql.load_users();
    mysql.disconnect();

    PostgresDriver pg;
    pg.connect("localhost:5432");

    UserRepository repo_pg(pg);
    repo_pg.load_users();
    pg.disconnect();
}