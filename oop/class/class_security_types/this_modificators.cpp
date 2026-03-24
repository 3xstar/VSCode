#include <iostream>

using namespace std;

class Book{
    public:
        Book(){
            this -> title = "";
            this -> author = "";
            this -> pages = 0;
            this -> price = 0.0;
        }
        
        Book& setTitle(const string& title){
            if(!title.empty()){
                this -> title = title;
            }
            return *this;
        }

        Book& setAuthor(const string& author){
            if(!author.empty()){
                this -> author = author;
            }
            return *this;
        }

        Book& setPages(const int& pages){
            if(pages > 0 && pages < 5000){
                this -> pages = pages;
            }
            return *this;
        }

        Book& setPrice(const double& price){
            if(price > 0){
                this -> price = price;
            }
            return *this;
        }

        string getTitle() const{
            return this -> title;
        }

        string getAuthor() const{
            return this -> author;
        }
        
        int getPages() const{
            return this -> pages;
        }

        void displayInfo() const{
            cout << "Книга: \nНазвание: " << this -> title << "\nАвтор: " << this -> author << "\nСтраницы: " << this -> pages << "\nЦена: " << this -> price;
        }

        bool hasMorePages(const Book& other) const{
            return this -> pages > other.pages;
        }
 

    private:
        string title;
        string author;
        int pages;
        double price;
};

int main(){
    Book book;
    book.setTitle("Война и мир")
        .setAuthor("Лев Толстой")
        .setPages(1200)
        .setPrice(900);

    Book book2;
    book2.setTitle("Преступление и наказание")
        .setAuthor("Федор Достоевский")
        .setPages(672)
        .setPrice(649.99);

    Book book3;
    book3.setTitle("1984")
        .setAuthor("Джордж Оруэлл")
        .setPages(320)
        .setPrice(449.99);

    book.displayInfo();
    cout << "\n";
    book2.displayInfo();
    cout << "\n";
    book3.displayInfo();
    cout << "\n";

    // Сравнение книг
    if(book.hasMorePages(book2)){
        cout << book.getTitle() << " больше, чем " << book2.getTitle() << endl;
    }

    if(book2.hasMorePages(book3)){
        cout << book2.getTitle() << " больше, чем " << book3.getTitle() << endl;
    }
    
}