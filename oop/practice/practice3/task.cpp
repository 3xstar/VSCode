#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Track {
protected:
    string title;
    int duration;
public:
    Track(string title, int duration)
    {
        this->title = title;
        this->duration = duration;
    }
    
    virtual void play()
    {
        cout << "Играет трек: " << title << endl;
    }

    virtual void getTitle()
    {
    	cout << "Название трека: " << title << endl;
    }
    
    virtual void getDuration()
    {
    	cout << "Длительность трека: " << duration << " минут" << endl;
    }

    bool operator<(const Track& other) const{
        return title < other.title;
    }
    
    virtual ~Track() {}
};


class Song : public Track {
private:
    string artist;
public:
    Song(string title, int duration, string artist)
     : Track(title, duration)
     {
     this->artist = artist;
     }
    
    void play() override
    {
        cout << "Играет песня: " << title << " - " << artist << endl;
    }
    
    void getTitle() override
    {
        cout << "Название песни: " << title << endl;
    }

    bool operator<(const Song& other) const{
        return title < other.title;
    }

    void getDuration() override
    {
    	cout << "Длительность песни: " << duration << " минут" << endl;
    }
};


class Instrumental : public Track {
private:
    string instrument;
public:
    Instrumental(string title, int duration, string instrument) : Track(title, duration)
    {
        this->instrument = instrument;
    }
    
    void play() override
    {
        cout << "Играет инструментал: " << title
             << " (" << instrument << ")" << endl;
    }

    void getTitle() override
    {
        cout << "Название инструментала: " << title << endl;
    }

    bool operator<(const Instrumental& other) const{
        return title < other.title;
    }

    void getDuration() override
    {
    	cout << "Длительность инструментала: " << duration << " минут" << endl;
    }
};


class Podcast : public Track{
private:
    string author;
    string guest;
public:
    Podcast(string title, int duration, string author, string guest) : Track(title, duration)
    {
    	this->author = author;
    	this->guest = guest;
    }
    
    void play() override
    {
    	cout << "Играет подкаст (" << title << ") от автора: " << author << "\nприглашенный гость: " << guest << endl;
    }

    void getTitle() override
    {
        cout << "Название подкаста: " << title << endl;
    }

    bool operator<(const Podcast& other) const{
        return title < other.title;
    }

    void getDuration() override
    {
    	cout << "Длительность подкаста: " << duration << " минут" << endl;
    }
};

vector<Track> sortPlaylist(vector<Track> playlist){
    sort(playlist.begin(), playlist.end());
    return playlist;
}

class Playlist{
    private:
        vector<Track> track_playlist;
        vector<Song> song_playlist;
        vector<Instrumental> instrumental_playlist;
        vector<Podcast> podcast_playlist;

    public:
        Playlist(){}

        void addTrack(Track track){
            track.getTitle();
            track_playlist.push_back(track);
            cout << "Трек был добавлен в плейлист треков!" << endl;
        }

        void addSong(Song song){
            song.getTitle();
            song_playlist.push_back(song);
            cout << "Песня была добавлен в плейлист песен!" << endl;
        }

        void addInstrumental(Instrumental instrumental){
            instrumental.getTitle();
            instrumental_playlist.push_back(instrumental);
            cout << "Инструментал был добавлен в плейлист инструментала!" << endl;
        }

        void addPodcast(Podcast podcast){
            podcast.getTitle();
            podcast_playlist.push_back(podcast);
            cout << "Подкаст был добавлен в плейлист подкастов!" << endl;
        }

        void Sort(){
            sort(track_playlist.begin(), track_playlist.end());
            sort(song_playlist.begin(), song_playlist.end());
            sort(instrumental_playlist.begin(), instrumental_playlist.end());
            sort(podcast_playlist.begin(), podcast_playlist.end());
            cout << "Все плейлисты были отсортированы!" << endl;
        }

        void showTracks(){
            cout << "Плейлист треков:" << endl;
            for_each(track_playlist.begin(), track_playlist.end(), [] (Track t)
            {
                t.getTitle();
            });
        }

        void showSongs(){
            cout << "Плейлист песен:" << endl;
            for_each(song_playlist.begin(), song_playlist.end(), [] (Song s)
            {
                s.getTitle();
            });
        }

        void showInstrumental(){
            cout << "Плейлист инструментала:" << endl;
            for_each(instrumental_playlist.begin(), instrumental_playlist.end(), [] (Instrumental i)
            {
                i.getTitle();
            });
        }

        void showPodcasts(){
            cout << "Плейлист подкастов:" << endl;
            for_each(podcast_playlist.begin(), podcast_playlist.end(), [] (Podcast p)
            {
                p.getTitle();
            });
        }
};


int main(){
    Playlist playlist;
    int action;
    while(true){
        cout << "=====МЕНЮ УПРАВЛЕНИЯ ПЛЕЙЛИСТОМ=====\n1 - Добавить трек в плейлист\n2 - Добавить песню в плейлист\n3 - Добавить инструментал в плейлист\n4 - Добавить подкаст в плейлист\n"
        "5 - Показать плейлист треков\n6 - Показать плейлист песен\n7 - Показать плейлист инструментала\n8 - Показать плейлист подкастов\n9 - Отсортировать плейлисты\n0 - Выход\nВыберите действие: ";
        cin >> action;
        cout << "\n";
        
        if(action == 1){
            string user_title;
            int user_duration;
            cout << "Введите название трека: ";
            cin >> user_title;
            cout << "Введите длительность трека в минутах (цифра): ";
            cin >> user_duration;
            playlist.addTrack(Track(user_title, user_duration));
            cout << "\n";
        }

        else if(action == 2){
            string user_title;
            int user_duration;
            string user_artist;
            cout << "Введите название песни: ";
            cin >> user_title;
            cout << "Введите длительность песни в минутах (цифра): ";
            cin >> user_duration;
            cout << "Введите имя артиста, исполнившего песню: ";
            cin >> user_artist;
            playlist.addSong(Song(user_title, user_duration, user_artist));
            cout << "\n";
        }

        else if(action == 3){
            string user_title;
            int user_duration;
            string user_instrument;
            cout << "Введите название инструментала: ";
            cin >> user_title;
            cout << "Введите длительность инструментала в минутах (цифра): ";
            cin >> user_duration;
            cout << "Введите применявшийся инструмент: ";
            cin >> user_instrument;
            playlist.addInstrumental(Instrumental(user_title, user_duration, user_instrument));
            cout << "\n";
        }

        else if(action == 4){
            string user_title;
            int user_duration;
            string user_author;
            string user_guest;
            cout << "Введите название подкаста: ";
            cin >> user_title;
            cout << "Введите длительность подкаста в минутах (цифра): ";
            cin >> user_duration;
            cout << "Введите имя автора подкаста: ";
            cin >> user_author;
            cout << "Введите имя гостя подкаста: ";
            cin >> user_guest;
            playlist.addPodcast(Podcast(user_title, user_duration, user_author, user_guest));
            cout << "\n";
        }

        else if(action == 5){
            playlist.showTracks();
            cout << "\n";
        }
        else if(action == 6){
            playlist.showSongs();
            cout << "\n";
        }
        else if(action == 7){
            playlist.showInstrumental();
            cout << "\n";
        }
        else if(action == 8){
            playlist.showPodcasts();
            cout << "\n";
        }

        else if(action == 9){
            playlist.Sort();
            cout << "\n";
        }
        
        else if(action == 0){
            break;
        }

        else{
            cout << "Неверный номер действия!" << endl;
            cout << "\n";
        }
    }
}