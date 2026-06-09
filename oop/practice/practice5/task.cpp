#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>


class LogEntry {
public:
 virtual void print() = 0;
 virtual std::string getType() = 0;

 std::string message;
 LogEntry(std:: string message){
    this->message = message;
 }

 virtual ~LogEntry() {}
};

class InfoLog : public LogEntry{
public:
 void print() override{
    std::cout << message << std:: endl;
 };
 std::string getType() override{
    return "INFO";
 };

 InfoLog(std:: string message) : LogEntry(message){
    this->message = message;
 }
 ~InfoLog() {};
};

class WarningLog : public LogEntry {
public:
 void print() override{
    std::cout << message << std:: endl;
 };
 std::string getType() override{
    return "WARNING";
 };

 WarningLog(std:: string message) : LogEntry(message){
    this->message = message;
 }

 ~WarningLog() {};
};


class ErrorLog : public LogEntry {
public:
 void print() override{
    std::cout << message << std:: endl;
 };
 std::string getType() override{
    return "ERROR";
 };

 ErrorLog(std:: string message) : LogEntry(message){
    this->message = message;
 }

 ~ErrorLog() {};
};

int main(){
    std::ifstream file("log.txt");
    std::string line;

    if(!file){
        std::cout << "File log.txt is not found";
        return 0;
    }
    else
    {
        std::vector<LogEntry*> logs;

        while(getline(file, line)){
            if(line.find("INFO:") == 0){
                logs.push_back(new InfoLog(line));
            }
            else if(line.find("WARNING:") == 0){
                logs.push_back(new WarningLog(line));
            }
            else if(line.find("ERROR:") == 0){
                logs.push_back(new ErrorLog(line));
            }
        }

        int info_count = 0;
        int warning_count = 0;
        int error_count = 0;
        
        std::cout << "Errors:" << std::endl;

        for(LogEntry* entry : logs){
            std::string type = entry->getType();

            if(type == "INFO"){
                info_count++;
            }

            else if(type == "WARNING"){
                warning_count++;
            }
            else if(type == "ERROR"){
                error_count++;
            }

            if(type == "ERROR"){
                entry->print();
            }
        }

        std::cout << std::endl;

        std::cout << "INFO: " << info_count << std::endl;
        std::cout << "WARNING: " << warning_count << std::endl;
        std::cout << "ERROR: " << error_count << std::endl;

        for(LogEntry* entry : logs){
            delete entry;
        }
    }
}