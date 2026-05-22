#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <limits>
#include <map>

using namespace std;

// Файл, хранящий данные:
const string DATA_FILE = "data.csv";

// Типы финансовых операций
enum OperationType{
    INCOME,
    EXPENSE
};

// Структура финансовой операции
struct Operation {
    int id;
    OperationType type;
    string category;
    double amount;
    string date;
    string description;
};

vector<Operation> operations;
int nextId = 1;

// Прототипы функций
void loadFromFile();
void saveToFile();
void addOperation();
void displayOperations();
void displayByType();
void displayByDateRange();
void deleteOperation();
void showStatistics();
void clearInputStream();
bool isValidDate(const string& date);

void loadFromFile() {
    ifstream file(DATA_FILE);
    string line;

    if(!file.is_open()){
        cout << "Файл не найден, будет создан новый при сохранении" << endl;
        return;
    }

    operations.clear();
    nextId = 1;

    while(getline(file, line)){
        if(line.empty()) continue;
        stringstream ss(line);
        string field;

        Operation op;

        getline(ss, field, ',');
        if(field.empty()) continue;
        op.id = stoi(field);

        getline(ss, field, ',');
        op.type = static_cast<OperationType>(stoi(field));

        getline(ss, field, ',');
        op.category = field;

        getline(ss, field, ',');
        op.amount = stod(field);

        getline(ss, field, ',');
        op.date = field;

        getline(ss, field, ',');
        op.description = field;

        operations.push_back(op);
        if(op.id >= nextId) {
            nextId = op.id + 1;
        }
    }
    
    file.close();
    cout << "Данные загружены из файла " << DATA_FILE << endl;
}

void saveToFile() {
    ofstream file(DATA_FILE);

    if(!file.is_open()){
        cout << "Ошибка: Не удалось открыть файл для записи" << endl;
        return;
    }

    for (const Operation& op : operations){
        file << op.id << ","
            << (op.type == INCOME ? "0" : "1") << ","
            << op.category << ","
            << op.amount << ","
            << op.date << ","
            << op.description << "\n";
    }

    file.close();
    cout << "Данные сохранены в файл " << DATA_FILE << endl;
}

void clearInputStream() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool isValidDate(const string& date) {
    if(date.length() != 10) return false;
    if(date[4] != '-' || date[7] != '-') return false;
    
    int year, month, day;
    char dash1, dash2;
    stringstream ss(date);
    ss >> year >> dash1 >> month >> dash2 >> day;
    
    if(ss.fail()) return false;
    if(year < 2000 || year > 2100) return false;
    if(month < 1 || month > 12) return false;
    if(day < 1 || day > 31) return false;
    
    return true;
}

void addOperation() {
    OperationType type;
    string category;
    double amount;
    string date;
    string description;
    int choice;
    
    cout << "\n--- Добавление операции ---\n";
    
    // Выбор типа
    cout << "Выберите тип операции:\n";
    cout << "1. Доход\n";
    cout << "2. Расход\n";
    cout << "Ваш выбор: ";
    cin >> choice;
    
    if(choice != 1 && choice != 2) {
        cout << "Неверный выбор!\n";
        clearInputStream();
        return;
    }
    
    type = (choice == 1) ? INCOME : EXPENSE;
    clearInputStream();
    
    // Ввод категории
    cout << "Введите категорию: ";
    getline(cin, category);
    
    // Ввод суммы
    cout << "Введите сумму: ";
    cin >> amount;
    
    if(amount <= 0) {
        cout << "Сумма должна быть положительной!\n";
        clearInputStream();
        return;
    }
    clearInputStream();
    
    // Ввод даты
    do {
        cout << "Введите дату (ГГГГ-ММ-ДД): ";
        getline(cin, date);
        if(!isValidDate(date)) {
            cout << "Неверный формат даты! Попробуйте снова.\n";
        }
    } while(!isValidDate(date));
    
    // Ввод описания
    cout << "Введите описание (можно оставить пустым): ";
    getline(cin, description);
    
    // Создание операции
    Operation op{nextId++, type, category, amount, date, description};
    operations.push_back(op);
    
    cout << "Операция успешно добавлена!\n";
    saveToFile();
}

void displayOperations() {
    if (operations.empty()) {
        cout << "Список операций пуст\n";
        return;
    }

    cout << "\n================== ВСЕ ОПЕРАЦИИ ==================\n";
    cout << left 
         << setw(5) << "ID" 
         << setw(10) << "Тип" 
         << setw(15) << "Категория" 
         << setw(12) << "Сумма" 
         << setw(12) << "Дата" 
         << "Описание\n";
    cout << string(80, '-') << endl;

    for(const auto& op : operations) {
        cout << left
             << setw(5) << op.id 
             << setw(10) << (op.type == INCOME ? "ДОХОД" : "РАСХОД") 
             << setw(15) << op.category 
             << setw(12) << fixed << setprecision(2) << op.amount 
             << setw(12) << op.date 
             << op.description << "\n";
    }
    cout << string(80, '=') << endl;
}

void displayByType() {
    if (operations.empty()) {
        cout << "Список операций пуст\n";
        return;
    }
    
    int choice;
    cout << "\nВыберите тип для просмотра:\n";
    cout << "1. Доходы\n";
    cout << "2. Расходы\n";
    cout << "Ваш выбор: ";
    cin >> choice;
    
    if(choice != 1 && choice != 2) {
        cout << "Неверный выбор!\n";
        clearInputStream();
        return;
    }
    
    OperationType type = (choice == 1) ? INCOME : EXPENSE;
    
    cout << "\n========== " << (type == INCOME ? "ДОХОДЫ" : "РАСХОДЫ") << " ==========\n";
    cout << left 
         << setw(5) << "ID" 
         << setw(15) << "Категория" 
         << setw(12) << "Сумма" 
         << setw(12) << "Дата" 
         << "Описание\n";
    cout << string(70, '-') << endl;

    bool found = false;
    double total = 0;
    
    for(const auto& op : operations) {
        if(op.type == type){
            found = true;
            total += op.amount;
            cout << left
                 << setw(5) << op.id 
                 << setw(15) << op.category 
                 << setw(12) << fixed << setprecision(2) << op.amount 
                 << setw(12) << op.date 
                 << op.description << "\n";
        }
    }

    if(found) {
        cout << string(70, '-') << endl;
        cout << "ИТОГО: " << fixed << setprecision(2) << total << endl;
    } else {
        cout << "Операции данного типа не найдены\n";
    }
    cout << string(70, '=') << endl;
}

void displayByDateRange() {
    if (operations.empty()) {
        cout << "Список операций пуст\n";
        return;
    }
    
    string startDate, endDate;
    clearInputStream();
    
    do {
        cout << "Введите начальную дату (ГГГГ-ММ-ДД): ";
        getline(cin, startDate);
        if(!isValidDate(startDate)) {
            cout << "Неверный формат даты!\n";
        }
    } while(!isValidDate(startDate));
    
    do {
        cout << "Введите конечную дату (ГГГГ-ММ-ДД): ";
        getline(cin, endDate);
        if(!isValidDate(endDate)) {
            cout << "Неверный формат даты!\n";
        }
    } while(!isValidDate(endDate));

    cout << "\n========== ОПЕРАЦИИ ЗА ПЕРИОД " << startDate << " - " << endDate << " ==========\n";
    cout << left 
         << setw(5) << "ID" 
         << setw(10) << "Тип" 
         << setw(15) << "Категория" 
         << setw(12) << "Сумма" 
         << setw(12) << "Дата" 
         << "Описание\n";
    cout << string(80, '-') << endl;

    bool found = false;
    double total = 0;
    
    for(const auto& op : operations) {
        if(op.date >= startDate && op.date <= endDate) {
            found = true;
            total += (op.type == INCOME) ? op.amount : -op.amount;
            cout << left
                 << setw(5) << op.id 
                 << setw(10) << (op.type == INCOME ? "ДОХОД" : "РАСХОД") 
                 << setw(15) << op.category 
                 << setw(12) << fixed << setprecision(2) << op.amount 
                 << setw(12) << op.date 
                 << op.description << "\n";
        }
    }
    
    if(found) {
        cout << string(80, '-') << endl;
        cout << "БАЛАНС ЗА ПЕРИОД: " << fixed << setprecision(2) << total << endl;
    } else {
        cout << "Операции за данный период не найдены\n";
    }
    cout << string(80, '=') << endl;
}

void deleteOperation() {
    if (operations.empty()) {
        cout << "Список операций пуст\n";
        return;
    }
    
    int id;
    cout << "Введите ID операции для удаления: ";
    cin >> id;
    
    auto it = find_if(operations.begin(), operations.end(), [id](const Operation& op) {
        return op.id == id;
    });
        
    if (it != operations.end()) {
        operations.erase(it);
        cout << "Операция с ID " << id << " успешно удалена\n";
        saveToFile();
    } else {
        cout << "Операция с ID " << id << " не найдена\n";
    }
    clearInputStream();
}

void showStatistics() {
    if (operations.empty()) {
        cout << "Нет операций для анализа\n";
        return;
    }
    
    double totalIncome = 0;
    double totalExpense = 0;
    map<string, double> incomeByCategory;
    map<string, double> expenseByCategory;
    
    for(const auto& op : operations) {
        if(op.type == INCOME) {
            totalIncome += op.amount;
            incomeByCategory[op.category] += op.amount;
        } else {
            totalExpense += op.amount;
            expenseByCategory[op.category] += op.amount;
        }
    }
    
    cout << "\n================== СТАТИСТИКА ==================\n";
    cout << "Общий доход: " << fixed << setprecision(2) << totalIncome << endl;
    cout << "Общий расход: " << totalExpense << endl;
    cout << "Текущий баланс: " << (totalIncome - totalExpense) << endl;
    
    cout << "\n--- Доходы по категориям ---\n";
    if(incomeByCategory.empty()) {
        cout << "Нет доходов\n";
    } else {
        for(const auto& cat : incomeByCategory) {
            cout << left << setw(20) << cat.first << ": " << cat.second << endl;
        }
    }
    
    cout << "\n--- Расходы по категориям ---\n";
    if(expenseByCategory.empty()) {
        cout << "Нет расходов\n";
    } else {
        for(const auto& cat : expenseByCategory) {
            cout << left << setw(20) << cat.first << ": " << cat.second << endl;
        }
    }
    cout << string(50, '=') << endl;
}

int main() {
    cout << "=== Учет финансов ===\n";
    
    // Загрузка данных при запуске
    loadFromFile();
    
    int choice;
    
    do {
        cout << "\n========== ГЛАВНОЕ МЕНЮ ==========\n";
        cout << "1. Добавить операцию\n";
        cout << "2. Показать все операции\n";
        cout << "3. Показать операции по типу\n";
        cout << "4. Показать операции за период\n";
        cout << "5. Удалить операцию\n";
        cout << "6. Показать статистику\n";
        cout << "7. Сохранить данные\n";
        cout << "0. Выход\n";
        cout << "===================================\n";
        cout << "Ваш выбор: ";
        
        cin >> choice;
        
        switch(choice) {
            case 1:
                addOperation();
                break;
            case 2:
                displayOperations();
                break;
            case 3:
                displayByType();
                break;
            case 4:
                displayByDateRange();
                break;
            case 5:
                deleteOperation();
                break;
            case 6:
                showStatistics();
                break;
            case 7:
                saveToFile();
                break;
            case 0:
                cout << "Сохранение данных перед выходом...\n";
                saveToFile();
                cout << "До свидания!\n";
                break;
            default:
                cout << "Неверный выбор! Попробуйте снова.\n";
                clearInputStream();
        }
    } while(choice != 0);
    
    return 0;
}