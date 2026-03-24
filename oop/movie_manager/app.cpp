#include <iostream>
#include <vector>
using namespace std;

/// @brief Фильм
class Movie{
    public:
        Movie(string title, string genre, double rating, int duration){
            this -> title = title;
            this -> genre = genre;
            this -> rating = rating;
            this -> duration = duration;
        }

        // Геттеры
        string getTitle(){return title;};
        string getGenre(){return genre;};
        double getRating(){return rating;};
        int getDuration(){return duration;};

        void display(){
            cout << "Фильм - " << title << "\nЖанр -" << genre << "\nРейтинг - " << rating << "\nДлительность -" << duration << endl; 
        }

    private:
        string title; // Название фильма
        string genre; // Жанр фильма
        double rating; // Рейтинг фильма
        int duration; // Длительность в минутах
};

/// @brief Каталог фильмов
class Catalog{
    public:
        /// @brief Добавление фильмов
        /// @param title Название фильма
        /// @param genre Жанр фильма
        /// @param rating Рейтинг фильма
        /// @param duration Длительность фильма
        void addMovie(string title, string genre, double rating, int duration){
            movies.push_back(Movie(title, genre, rating, duration));
            cout << "Фильм добавлен\n";
        }

        /// @brief Удаление фильмов
        /// @param title Название фильма
        void removeMovie(string title){
            for(int i = 0; i < movies.size(); i++){
                if(movies[i].getTitle() == title){
                    movies.erase(movies.begin() + i);
                }
            }
        }

        /// @brief Поиск по заголовку
        /// @param title Название фильма
        void findByTitle(string title){
            bool found = false;
            for(Movie movie : movies){
                if(movie.getTitle() == title){
                    movie.display();
                    found = true;
                }
            }
        }

        /// @brief Просмотр всех фильмов
        void showMovies(){
            for(Movie movie : movies){
                movie.display();
            }
        }

    private:
        vector<Movie> movies; // Список(вектор) фильмов
};

int main(){
    Catalog movies; // Каталог фильмов
    int choice; // Действие
    do{
        cout << "=====MOVIES LIBRARY=====" << endl;
        cout << "1. Show Movies" << endl;
        cout << "2. Add Movie" << endl;
        cout << "3. Find Movie" << endl;
        cout << "4. Remove Movie" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;

        cin.ignore();
        switch(choice){ // Очистка
            case 1:
                movies.showMovies();
                break;

            case 2:{
                string title, genre;
                double rating;
                int duration;

                cout << "Название: ";
                getline(cin, title);
                cout << endl;

                cout << "Жанр: ";
                getline(cin, genre);
                cout << endl;

                cout << "Рейтинг: ";
                cin >> rating;
                cout << endl;

                cout << "Длительность: ";
                cin >> duration;
                cout << endl;
                break;
            }

            case 3:{
                string title;
                cout << "Введите название: ";
                getline(cin, title);
                movies.findByTitle(title);
                break;
            }
                
            case 4:{
                string title;
                cout << "Введите название: ";
                getline(cin, title);
                movies.removeMovie(title);
                break;
            }

            case 0:
                cout << "Выход из программы...";
                break;
            
            default:
                cout << "Fail" << endl;
        } 
} while(choice != 0);
}